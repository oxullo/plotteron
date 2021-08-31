//
//  plotteronapp.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#ifndef plotteronapp_hpp
#define plotteronapp_hpp

#include <Mahi/Gui.hpp>


class PlotteronApp : public mahi::gui::Application {
public:
    PlotteronApp(const Application::Config config) : mahi::gui::Application(config) {};
    
    void update() override;
};


#endif /* plotteronapp_hpp */
