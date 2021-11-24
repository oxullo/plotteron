//
//  plotwidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 06.09.21.
//

#include <iostream>

#include <Mahi/Util/Logging/Log.hpp>

#include "plotwidget.hpp"

using namespace mahi::util;


PlotWidget::PlotWidget(App& app) : Widget(app), history_length(10)
{
}

void PlotWidget::update()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::BeginFixed("Plot", position, size, ImGuiWindowFlags_NoTitleBar);

    ImGui::SliderFloat("History", &history_length, 1, 60, "%.1f s");

    float max_x = buffer.get_max_x() - history_length * 1000000000;

    if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, -1))) {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoTickLabels, ImPlotAxisFlags_AutoFit);
        ImPlot::SetupAxisLimits(ImAxis_X1, max_x, buffer.get_max_x(), ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0,1);

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
    try {
        double value = point.get_value();
        buffer.add_point(point.get_timestamp(), point.get_value());
    } catch (const std::invalid_argument& exc) {
        LOG(Error) << "Unable to parse line: " << point.get_raw_line();
    }
}

void PlotWidget::set_history_length(float seconds)
{
    history_length = seconds;
}

void PlotWidget::clear_points()
{
    buffer.erase();
}
