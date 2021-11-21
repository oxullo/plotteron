//
//  serialport.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 08.09.21.
//

#include <cassert>
#include <iostream>
#include <random>

#include <Mahi/Util/Logging/Log.hpp>

#include "serialport.hpp"

using namespace mahi::util;


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

void SerialPort::connect(std::string dev_path)
{
    disconnect();
    open_port(dev_path);
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

//    std::default_random_engine generator;
//    std::uniform_real_distribution<double> distribution(0.0,1.0);

    connection_time = std::chrono::steady_clock::now();
    char read_buffer[128];
    std::stringbuf line_buffer;
    std::ostream os (&line_buffer);

    while (connected) {
        int bytes_read = sp_blocking_read_next(port, read_buffer, 128, 100);
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

bool SerialPort::open_port(std::string port_name)
{
    if (sp_get_port_by_name(port_name.c_str(), &port) != SP_OK) {
        LOG(Error) << "Cannot find a port named " << port_name;
        return false;
    }

    LOG(Info) << "Opened port: " << sp_get_port_description(port);

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

    // TODO: check each RC
    // TODO: port configuration to runtime options
    sp_set_baudrate(port, 115200);
    sp_set_bits(port, 8);
    sp_set_parity(port, SP_PARITY_NONE);
    sp_set_stopbits(port, 1);
    sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);

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
    double value = std::stod(line);
    std::chrono::duration<double, std::nano> duration = std::chrono::steady_clock::now() - connection_time;
    data_queue.emplace(duration.count(), value);

}
