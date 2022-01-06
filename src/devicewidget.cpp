/**
 * Plotteron
 *
 * Copyright (C) 2021 OXullo Intersecans <x@xul.it>
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "devicewidget.hpp"

namespace {

const std::map<int, const char*> baudrates {
    {9600, "9600"},
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
        Sample point = serial_port.data_queue.front();
        serial_port.data_queue.pop();
        on_point_acquired.emit(point);
    }
    ImGui::End();
}
