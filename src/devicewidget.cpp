//
//  devicewidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 31.08.21.
//

#include "devicewidget.hpp"

void DeviceWidget::update()
{
//    ImGui::BeginFixed("Device", position, size, ImGuiWindowFlags_NoTitleBar);
    ImGui::Begin("Device");
    ImGui::BeginGroup();

    ImGui::PushItemWidth(200);
    if (ImGui::BeginCombo("##serial_device", "Serial device"))
    {
        ImGui::Selectable("1234");
        ImGui::Selectable("abc");
        ImGui::Selectable("444");
        ImGui::Selectable("1231114");
//        for (auto &pair : m_available)
//        {
//            bool isSelected = m_currentApi == pair.first;
//            if (ImGui::Selectable(pair.first.c_str(), isSelected))
//            {
//                switchApi(pair.first);
//            }
//            if (isSelected)
//                ImGui::SetItemDefaultFocus();
//        }
        ImGui::EndCombo();
    }
    ImGui::PopItemWidth();
//    gui.status.showTooltip("Sel2ct API");

    ImGui::EndGroup();
    ImGui::End();
}
