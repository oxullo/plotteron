//
//  devicewidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#include "devicewidget.hpp"

void DeviceWidget::update()
{
    ImGui::BeginFixed("Device", position, size, ImGuiWindowFlags_NoTitleBar);
    ImGui::BeginGroup();
    ImGui::Button("Hellow");
    ImGui::EndGroup();
    ImGui::End();
}
