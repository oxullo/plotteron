//
//  plotteronapp.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#ifndef plotteronapp_hpp
#define plotteronapp_hpp

#include <Mahi/Gui.hpp>

#include "serialport.hpp"
#include "devicewidget.hpp"
#include "plotwidget.hpp"


class PlotteronApp : public mahi::gui::Application {
public:
    PlotteronApp(const Application::Config config);
    
    void update() override;

private:
    SerialPort serial_port;
    DeviceWidget device_widget;
    PlotWidget plot_widget;
    
    void reposition_widgets();
};


#endif /* plotteronapp_hpp */
