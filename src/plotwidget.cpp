//
//  plotwidget.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 06.09.21.
//

#include "plotwidget.hpp"

struct ScrollingBuffer {
    int max_size;
    int offset;
    ImVector<ImVec2> data;
    
    ScrollingBuffer(int max_size_=2000) {
        max_size = max_size_;
        offset = 0;
        data.reserve(max_size);
    }
    
    void add_point(float x, float y) {
        if (data.size() < max_size)
            data.push_back(ImVec2(x,y));
        else {
            data[offset] = ImVec2(x,y);
            offset = (offset + 1) % max_size;
        }
    }
    
    void erase() {
        if (data.size() > 0) {
            data.shrink(0);
            offset = 0;
        }
    }
};

void PlotWidget::update()
{
    ImGui::BeginFixed("Plot", position, size, ImGuiWindowFlags_NoTitleBar);

    static ScrollingBuffer buffer1, buffer2;
    static float t = 0;
    t += ImGui::GetIO().DeltaTime;
    buffer1.add_point(t, sin(t));
    buffer2.add_point(t, sin(t*1.5));

    static ImPlotAxisFlags rt_axis = ImPlotAxisFlags_NoTickLabels;
    ImPlot::SetNextPlotLimitsX(t - 20, t, ImGuiCond_Always);
    if (ImPlot::BeginPlot("##Scrolling", NULL, NULL, size, rt_axis, rt_axis | ImPlotAxisFlags_LockMin)) {
        ImPlot::PlotLine("Sin", &buffer1.data[0].x, &buffer1.data[0].y, buffer1.data.size(), buffer1.offset, 2 * sizeof(float));
        ImPlot::PlotLine("Sin +", &buffer2.data[0].x, &buffer2.data[0].y, buffer2.data.size(), buffer2.offset, 2 * sizeof(float));
        ImPlot::EndPlot();
    }
    
    ImGui::End();
}
