//
//  plotwidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 06.09.21.
//

#include <iostream>

#include "plotwidget.hpp"


void PlotWidget::update()
{
    ImGui::BeginFixed("Plot", position, size, ImGuiWindowFlags_NoTitleBar);

    static ImPlotAxisFlags rt_axis = ImPlotAxisFlags_NoTickLabels;
    ImPlot::SetNextPlotLimitsX(buffer.get_min_x(), buffer.get_max_x(), ImGuiCond_Always);
    if (ImPlot::BeginPlot("##Scrolling", NULL, NULL, size, rt_axis, rt_axis | ImPlotAxisFlags_LockMin)) {
        if (buffer.data.size() > 0) {
            ImPlot::PlotLine("Points", &buffer.data[0].x, &buffer.data[0].y, buffer.data.size(), buffer.offset, 2 * sizeof(float));
        }
        ImPlot::EndPlot();
    }
    
    ImGui::End();
}

void PlotWidget::add_point(DataPoint &point)
{
    std::cerr << "DP ts=" << point.get_timestamp() << " v=" << point.get_value() << std::endl;
    buffer.add_point(point.get_timestamp(), point.get_value());
}
