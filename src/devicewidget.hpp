//
//  devicewidget.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#ifndef devicewidget_hpp
#define devicewidget_hpp

#include "widget.hpp"

class DeviceWidget : public Widget {
public:
    DeviceWidget() : Widget() {};
    void update() override;
};

#endif /* devicewidget_hpp */
