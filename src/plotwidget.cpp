//
//  plotwidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 06.09.21.
//

#include <iostream>

#include "plotwidget.hpp"

PlotWidget::PlotWidget(PlotteronApp& app) : Widget(app), history_length(10)
{
}

void PlotWidget::update()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::BeginFixed("Plot", position, size, ImGuiWindowFlags_NoTitleBar);
//    ImGui::Begin("Plot");

    ImGui::SliderFloat("History", &history_length, 1, 60, "%.1f s");

    static ImPlotAxisFlags rt_axis = ImPlotAxisFlags_NoTickLabels;
    float max_x = buffer.get_max_x() - history_length * 1000000000;

    ImPlot::SetNextPlotLimitsX(max_x, buffer.get_max_x(), ImGuiCond_Always);
    if (ImPlot::BeginPlot("##Scrolling", NULL, NULL, ImVec2(-1, -1), rt_axis, rt_axis | ImPlotAxisFlags_LockMin)) {
        if (buffer.data.size() > 0) {
            ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL,0.5f);
            ImPlot::PlotLine("Points", &buffer.data[0].x, &buffer.data[0].y, buffer.data.size(), buffer.offset, 2 * sizeof(float));
        }
        ImPlot::EndPlot();
    }

    ImGui::End();
}

void PlotWidget::add_point(DataPoint &point)
{
//    std::cerr << "DP ts=" << point.get_timestamp() << " v=" << point.get_value() << std::endl;
    buffer.add_point(point.get_timestamp(), point.get_value());
}

void PlotWidget::set_history_length(float seconds)
{
    history_length = seconds;
}
