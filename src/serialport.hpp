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
#include <libserialport.h>


class SerialPort {
public:
    SerialPort();
    ~SerialPort();

    void connect(std::string dev_path);
    void disconnect();
    std::vector<std::string> get_available_ports();
    
private:
    std::thread connection_thread;
    bool is_connected;
    
    void connection_handler();
    void dump_ports();
};

#endif /* serialport_hpp */
