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
    PlotWidget(PlotteronApp& app);

    void update() override;
    void add_point(DataPoint& point);
    void clear_points();
    void set_history_length(float seconds);

//private:
    ScrollingBuffer buffer;
    float history_length;
};

#endif /* plotwidget_hpp */
