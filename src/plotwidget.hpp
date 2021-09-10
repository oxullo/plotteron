//
//  plotwidget.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 06.09.21.
//

#ifndef plotwidget_hpp
#define plotwidget_hpp

#include "scrollingbuffer.hpp"
#include "datapoint.hpp"
#include "widget.hpp"

class PlotWidget : public Widget {
public:
    PlotWidget() : Widget() {};
    void update() override;
    void add_point(DataPoint& point);
    
//private:
    ScrollingBuffer buffer;
};

#endif /* plotwidget_hpp */
