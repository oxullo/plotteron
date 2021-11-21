//
//  plotteronapp.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#ifndef plotteronapp_hpp
#define plotteronapp_hpp

#include <Mahi/Gui.hpp>

#include "devicewidget.hpp"
#include "plotwidget.hpp"


class PlotteronApp : public mahi::gui::Application {
public:
    PlotteronApp(const Application::Config config);

    void update() override;

private:
    void reposition_widgets();

    DeviceWidget device_widget;
    PlotWidget plot_widget;
    float history_length;
};


#endif /* plotteronapp_hpp */
