//
//  plotwidget.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 06.09.21.
//

#ifndef plotwidget_hpp
#define plotwidget_hpp

#include "widget.hpp"

class PlotWidget : public Widget {
public:
    PlotWidget() : Widget() {};
    void update() override;
};

#endif /* plotwidget_hpp */
