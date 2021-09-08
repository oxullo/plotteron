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
    device_widget(),
    plot_widget()
{
}

void PlotteronApp::update()
{
    reposition_widgets();
    device_widget.update();
    plot_widget.update();
    std::cerr << "size: x=" << ImGui::GetMainViewport()->Size.x << " y=" << ImGui::GetMainViewport()->Size.y << std::endl;
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
