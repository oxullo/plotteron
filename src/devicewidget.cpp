//
//  devicewidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#include "devicewidget.hpp"

DeviceWidget::DeviceWidget(PlotteronApp& app) :
    Widget(app),
    serial_port()
{
}

void DeviceWidget::update()
{
    ImGui::BeginFixed("Device", position, ImVec2(size.x, 100), ImGuiWindowFlags_NoTitleBar);
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

    while (!serial_port.data_queue.empty()) {
        DataPoint point = serial_port.data_queue.front();
        serial_port.data_queue.pop();
        on_point_acquired.emit(point);
//        plot_widget.add_point(point);
    }
    ImGui::End();
}
