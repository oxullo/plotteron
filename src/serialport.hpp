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
#include <libserialport.h>

#include "datapoint.hpp"


class SerialPort {
public:
    SerialPort();
    ~SerialPort();

    void connect(std::string dev_path);
    void disconnect();
    void dump_ports();
    std::vector<std::string> get_available_ports();

    std::queue<DataPoint> data_queue;

private:
    void connection_handler();

    std::thread connection_thread;
    bool is_connected;
};

#endif /* serialport_hpp */
