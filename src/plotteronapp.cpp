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
    serial_port(),
    device_widget(),
    plot_widget()
{
}

void PlotteronApp::update()
{
    static bool enabled = false;
    
    reposition_widgets();
    device_widget.update();
    if (true ||enabled) {
        plot_widget.update();
    }
//    std::cerr << "size: x=" << ImGui::GetMainViewport()->Size.x << " y=" << ImGui::GetMainViewport()->Size.y << std::endl;
    if (ImGui::Button("Start")) {
        serial_port.connect("/dev/tty.usbmodem14401");
        std::vector<std::string> v = serial_port.get_available_ports();
        
        for(const auto& value: v) {
            std::cerr << value << std::endl;
        }
        enabled = true;
    }
    
    ImGui::SameLine();
    
    if (ImGui::Button("Stop")) {
        serial_port.disconnect();
        enabled = false;
    }
    
    ImGui::Text("Offset: %d", plot_widget.buffer.offset);
    ImGui::Text("Size: %d", plot_widget.buffer.data.size());
    static float history_length = 1;
    if (ImGui::SliderFloat("History", &history_length, 1, 60, "%.1f s")) {
        plot_widget.set_history_length(history_length);
    }

    while (!serial_port.data_queue.empty()) {
        DataPoint point = serial_port.data_queue.front();
        serial_port.data_queue.pop();
        plot_widget.add_point(point);
    }
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
