//
//  serialport.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 08.09.21.
//

#include <chrono>
#include <cassert>
#include <iostream>
#include <random>

#include "serialport.hpp"

SerialPort::SerialPort() :
    connection_thread(),
    is_connected(false)
{
}

SerialPort::~SerialPort()
{
    disconnect();
}

std::vector<std::string> SerialPort::get_available_ports()
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
    connection_thread = std::thread(&SerialPort::connection_handler, this);
}

void SerialPort::disconnect()
{
    is_connected = false;
    if (connection_thread.joinable()) {
        connection_thread.join();
    }
}

void SerialPort::connection_handler()
{
    is_connected = true;
    std::cerr << "Connection handler started" << std::endl;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    std::chrono::steady_clock::time_point connection_time = std::chrono::steady_clock::now();
    while (is_connected) {
        std::chrono::duration<double, std::nano> duration = std::chrono::steady_clock::now() - connection_time;
        data_queue.emplace(duration.count(), distribution(generator));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::cerr << "Connection handler terminated" << std::endl;
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
                std::cerr << "Type: USB" << std::endl;

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
