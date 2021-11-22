//
//  devicewidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#include "devicewidget.hpp"

namespace {

const std::map<int, const char*> baudrates {
    {38400, "38400"},
    {57600, "57600"},
    {115200, "115200"},
};

}

DeviceWidget::DeviceWidget(App& app) :
    Widget(app),
    serial_port(),
    current_baudrate(115200)
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

    ImGui::SameLine();

    if (ImGui::BeginCombo("Baudrate", baudrates.at(current_baudrate))) {
        for (const auto &[baudrate, baudrate_chr] : baudrates) {
            if (ImGui::Selectable(baudrate_chr, current_baudrate == baudrate)) {
                current_baudrate = baudrate;
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
                serial_port.connect(selected_device, current_baudrate);
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
