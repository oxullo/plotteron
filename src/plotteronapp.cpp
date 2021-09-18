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
    plot_widget(),
    history_length(10)
{
    plot_widget.set_history_length(history_length);
}

void PlotteronApp::update()
{
//    reposition_widgets();
//    device_widget.update();
    plot_widget.update();

    if (ImGui::BeginCombo("Serial device", selected_device.c_str())) {
        std::vector<std::string> devices = serial_port.get_available_devices();

        for (const std::string& value: devices) {
            if (ImGui::Selectable(value.c_str(), selected_device == value)) {
                selected_device = value;
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::Button("Start")) {
        serial_port.connect(selected_device);
    }

    ImGui::SameLine();

    if (ImGui::Button("Stop")) {
        serial_port.disconnect();
    }

    ImGui::Text("Offset: %d", plot_widget.buffer.offset);
    ImGui::Text("Size: %d", plot_widget.buffer.data.size());
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
