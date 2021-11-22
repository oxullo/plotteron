//
//  devicewidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#include "devicewidget.hpp"

DeviceWidget::DeviceWidget(App& app) :
    Widget(app),
    serial_port()
{
}

void DeviceWidget::update()
{
    ImGui::BeginFixed("Device", position, size, ImGuiWindowFlags_NoTitleBar);
    ImGui::PushItemWidth(150);
    if (ImGui::BeginCombo("Serial device", selected_device.c_str())) {
        std::vector<std::string> devices = serial_port.get_available_devices();

        for (const std::string& value: devices) {
            if (ImGui::Selectable(value.c_str(), selected_device == value)) {
                selected_device = value;
            }
        }
        ImGui::EndCombo();
    }
    ImGui::PopItemWidth();

    ImGui::SameLine();

    if (!selected_device.empty()) {
        if (serial_port.is_connected()) {
            if (ImGui::Button("Disconnect")) {
                serial_port.disconnect();
            }
        } else {
            if (ImGui::Button("Connect")) {
                serial_port.connect(selected_device);
                on_connected.emit();
            }
        }
    }

    while (!serial_port.data_queue.empty()) {
        DataPoint point = serial_port.data_queue.front();
        serial_port.data_queue.pop();
        on_point_acquired.emit(point);
    }
    ImGui::End();
}
