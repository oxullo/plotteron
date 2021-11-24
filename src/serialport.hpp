//
//  serialport.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 08.09.21.
//

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
