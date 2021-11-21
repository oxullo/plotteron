//
//  widget.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#ifndef widget_hpp
#define widget_hpp

#include <Mahi/Gui.hpp>

class PlotteronApp;

class Widget {
public:
    Widget(PlotteronApp& app);
    virtual void update() { };

    mahi::gui::Vec2 position, size;

private:
    PlotteronApp& app;
};

#endif /* widget_hpp */
