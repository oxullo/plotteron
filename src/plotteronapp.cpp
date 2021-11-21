//
//  plotteronapp.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#include <iostream>

#include "plotteronapp.hpp"

PlotteronApp::PlotteronApp(const Application::Config config) :
    mahi::gui::Application(config),
    device_widget(*this),
    plot_widget(*this),
    history_length(10)
{
    plot_widget.set_history_length(history_length);

    device_widget.on_point_acquired.connect(plot_widget, &PlotWidget::add_point);
    device_widget.on_connected.connect(plot_widget, &PlotWidget::clear_points);
}

void PlotteronApp::update()
{
    reposition_widgets();
    plot_widget.update();
    device_widget.update();
}

void PlotteronApp::reposition_widgets()
{
    ImVec2 viewport_pos = ImGui::GetMainViewport()->Pos;
    ImVec2 viewport_size = ImGui::GetMainViewport()->Size;

    device_widget.position = viewport_pos;
    device_widget.size = ImVec2(viewport_size.x, 50);

    plot_widget.position = ImVec2(viewport_pos.x, viewport_pos.y + 50);
    plot_widget.size = ImVec2(viewport_size.x, viewport_size.y - 50);
}
