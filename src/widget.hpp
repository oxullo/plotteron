//
//  widget.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#ifndef widget_hpp
#define widget_hpp

#include <Mahi/Gui.hpp>

class App;

class Widget {
public:
    Widget(App& app);
    virtual void update() { };

    mahi::gui::Vec2 position, size;

private:
    App& app;
};

#endif /* widget_hpp */
