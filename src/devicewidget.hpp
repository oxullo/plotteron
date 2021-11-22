//
//  devicewidget.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#ifndef devicewidget_hpp
#define devicewidget_hpp

#include "widget.hpp"
#include "serialport.hpp"

class DeviceWidget : public Widget {
public:
    DeviceWidget(App& app);
    void update() override;

    mahi::util::Event<void(DataPoint&)> on_point_acquired;
    mahi::util::Event<void(void)> on_connected;

private:
    SerialPort serial_port;
    std::string selected_device;
};

#endif /* devicewidget_hpp */
