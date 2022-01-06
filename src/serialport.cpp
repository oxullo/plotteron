/**
 * Plotteron
 *
 * Copyright (C) 2021 OXullo Intersecans <x@xul.it>
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <cassert>
#include <iostream>
#include <random>

#include <Mahi/Util/Logging/Log.hpp>

#include "serialport.hpp"

using namespace mahi::util;

namespace {
const int READ_BUFFER_SIZE = 128;
const int READ_TIMEOUT = 100;
}


SerialPort::SerialPort() :
    connection_thread(),
    connected(false),
    port(NULL)
{
}

SerialPort::~SerialPort()
{
    disconnect();
}

std::vector<std::string> SerialPort::get_available_devices()
{
    struct sp_port** ports;

    enum sp_return result = sp_list_ports(&ports);

    assert(result == SP_OK);

    std::vector<std::string> port_names;

    for (uint8_t i = 0; ports[i] != NULL; i++) {
        port_names.push_back(std::string(sp_get_port_name(ports[i])));
    }

    sp_free_port_list(ports);

    return port_names;
}

void SerialPort::connect(std::string dev_path, int baudrate)
{
    disconnect();
    open_port(dev_path, baudrate);
    connection_thread = std::thread(&SerialPort::connection_handler, this);
}

void SerialPort::disconnect()
{
    connected = false;
    if (connection_thread.joinable()) {
        connection_thread.join();
    }
}

void SerialPort::connection_handler()
{
    connected = true;
    LOG(Verbose) << "Connection handler started";

    connection_time = std::chrono::steady_clock::now();
    char read_buffer[READ_BUFFER_SIZE];
    std::stringbuf line_buffer;
    std::ostream os (&line_buffer);

    sp_flush(port, SP_BUF_INPUT);

    while (connected) {
        int bytes_read = sp_blocking_read_next(port, read_buffer,
                READ_BUFFER_SIZE, READ_TIMEOUT);
        if (bytes_read > 0) {
            for (int i = 0; i < bytes_read; ++i) {
                char c = read_buffer[i];
                if (c == '\n') {
                    process_line(line_buffer.str());
                    line_buffer.str("");
                } else if (c != '\r') {
                    os << c;
                }
            }
        }
    }

    close_port();

    LOG(Verbose) << "Connection handler terminated";
}

void SerialPort::dump_ports()
{
    struct sp_port** ports;

    enum sp_return result = sp_list_ports(&ports);

    for (uint8_t i = 0; ports[i] != NULL; i++) {
        struct sp_port *port = ports[i];

        std::cerr << "Port: " << sp_get_port_name(port) << std::endl;
        std::cerr << "  Description: " << sp_get_port_description(port) << std::endl;

        enum sp_transport transport = sp_get_port_transport(port);

        if (transport == SP_TRANSPORT_NATIVE) {
                /* This is a "native" port, usually directly connected
                 * to the system rather than some external interface. */
                std::cerr << "  Type: Native" << std::endl;
        } else if (transport == SP_TRANSPORT_USB) {
                /* This is a USB to serial converter of some kind. */
                std::cerr << "  Type: USB" << std::endl;

                /* Display string information from the USB descriptors. */
                std::cerr << "  Manufacturer: " << sp_get_port_usb_manufacturer(port) << std::endl;
                std::cerr << "  Product: " << sp_get_port_usb_product(port) << std::endl;
                std::cerr << "  Serial: " << sp_get_port_usb_serial(port) << std::endl;

                /* Display USB vendor and product IDs. */
                int usb_vid, usb_pid;
                sp_get_port_usb_vid_pid(port, &usb_vid, &usb_pid);
                std::cerr << "  VID: " << usb_vid << " PID: " << usb_pid << std::endl;

                /* Display bus and address. */
                int usb_bus, usb_address;
                sp_get_port_usb_bus_address(port, &usb_bus, &usb_address);
                std::cerr << "  Bus: " << usb_bus << " Address: " << usb_address << std::endl;
        } else if (transport == SP_TRANSPORT_BLUETOOTH) {
                /* This is a Bluetooth serial port. */
                std::cerr << "  Type: Bluetooth" << std::endl;

                /* Display Bluetooth MAC address. */
                std::cerr << "  MAC: " << sp_get_port_bluetooth_address(port) << std::endl;
        }
    }

    sp_free_port_list(ports);
}

bool SerialPort::open_port(std::string port_name, int baudrate)
{
    if (sp_get_port_by_name(port_name.c_str(), &port) != SP_OK) {
        LOG(Error) << "Cannot find a port named " << port_name;
        return false;
    }

    enum sp_return rc = sp_open(port, SP_MODE_READ_WRITE);
    if (rc != SP_OK) {
        if (rc == SP_ERR_FAIL) {
            char* error_message = sp_last_error_message();
            LOG(Error) << "Cannot open port " << port_name << ": " << error_message;
            sp_free_error_message(error_message);
        }
        sp_free_port(port);
        return false;
    }

    if (sp_set_baudrate(port, baudrate) != SP_OK) {
        LOG(Error) << "Cannot open port " << port_name << ": invalid baudrate " << baudrate;
        sp_free_port(port);
        return false;
    }

    // TODO: port configuration to runtime options
    if (sp_set_bits(port, 8) != SP_OK) {
        LOG(Error) << "Cannot open port " << port_name << ": unable to set 8 bits operation";
        sp_free_port(port);
        return false;
    }

    if (sp_set_parity(port, SP_PARITY_NONE) != SP_OK) {
        LOG(Error) << "Cannot open port " << port_name << ": unable to set no parity operation";
        sp_free_port(port);
        return false;
    }

    if (sp_set_stopbits(port, 1) != SP_OK) {
        LOG(Error) << "Cannot open port " << port_name << ": unable to set 1 bit stop operation";
        sp_free_port(port);
        return false;
    }

    if (sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE) != SP_OK) {
        LOG(Error) << "Cannot open port " << port_name << ": unable to set no flow control operation";
        sp_free_port(port);
        return false;
    }

    LOG(Info) << "Opened port: " << sp_get_port_description(port) << " baudrate: " << baudrate;

    return true;
}

void SerialPort::close_port()
{
    LOG(Info) << "Closing port: " << sp_get_port_description(port);

    if (sp_close(port) != SP_OK) {
        LOG(Error) << "Error while closing port";
    }
    sp_free_port(port);
}

void SerialPort::process_line(std::string line)
{
//    std::cerr << "Line: |" << line << "|" << std::endl;
    std::chrono::duration<double, std::nano> duration = std::chrono::steady_clock::now() - connection_time;
    data_queue.emplace(duration.count(), line);

}
