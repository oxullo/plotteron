//
//  widget.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#ifndef widget_hpp
#define widget_hpp

#include <Mahi/Gui.hpp>

class Widget {
public:
    Widget();
    virtual void update() { };

    mahi::gui::Vec2 position, size;
};

#endif /* widget_hpp */
