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

#ifndef serialport_hpp
#define serialport_hpp

#include <thread>
#include <vector>
#include <string>
#include <queue>
#include <chrono>

#include <libserialport.h>

#include "sample.hpp"


class SerialPort {
public:
    SerialPort();
    ~SerialPort();

    void connect(std::string dev_path, int baudrate);
    void disconnect();
    void dump_ports();
    std::vector<std::string> get_available_devices();

    bool is_connected() const
    {
        return connected;
    }

    std::queue<Sample> data_queue;

private:
    void connection_handler();
    bool open_port(std::string port_name, int baudrate);
    void close_port();
    void process_line(std::string line);

    std::thread connection_thread;
    bool connected;
    struct sp_port *port;
    std::chrono::steady_clock::time_point connection_time;
};

#endif /* serialport_hpp */
