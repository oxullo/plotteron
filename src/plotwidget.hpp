//
//  plotwidget.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 06.09.21.
//

#ifndef plotwidget_hpp
#define plotwidget_hpp

#include "sample.hpp"
#include "scrollingbuffer.hpp"
#include "widget.hpp"

class PlotWidget : public Widget {
public:
    PlotWidget(App& app);

    void update() override;
    void add_point(Sample& point);
    void clear_points();
    void set_history_length(float seconds);

private:
    std::vector<ScrollingBuffer> buffers;
    float history_length;
};

#endif /* plotwidget_hpp */
