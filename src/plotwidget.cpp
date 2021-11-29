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

#include <iostream>

#include <Mahi/Util/Logging/Log.hpp>

#include "plotwidget.hpp"

using namespace mahi::util;


PlotWidget::PlotWidget(App& app) : Widget(app), history_length(10)
{
}

void PlotWidget::update()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::BeginFixed("Plot", position, size, ImGuiWindowFlags_NoTitleBar);

    ImGui::SliderFloat("History", &history_length, 1, 60, "%.1f s");

    if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, -1))) {
        if (buffers.size() > 0) {
            float max_x = buffers[0].get_max_x() - history_length * 1000000000;

            ImPlot::SetupAxes(NULL, NULL,
                    ImPlotAxisFlags_NoTickLabels, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisLimits(ImAxis_X1, max_x,
                    buffers[0].get_max_x(), ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);

            int index = 1;
            ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
            for (auto buffer : buffers) {
                std::string legend = "Track " + std::to_string(index++);
                ImPlot::PlotLine(legend.c_str(),
                        &buffer.data[0].x, &buffer.data[0].y,
                        buffer.data.size(), buffer.offset, 2 * sizeof(float));
            }
        }
        ImPlot::EndPlot();
    }

    ImGui::End();
}

void PlotWidget::add_point(Sample& sample)
{
    std::string line = sample.get_raw_line();

    std::istringstream iss(line);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());

    std::vector<double> values;

    for (auto entry : results) {
        try {
            double value = std::stod(entry);
            values.push_back(value);
        } catch (const std::invalid_argument& exc) {
            LOG(Error) << "Unable to parse line: " << line;
            return;
        }
    }

    if (values.size() > 0) {
        if (buffers.size() < values.size()) {
            LOG(Info) << "Line: " << line;
            LOG(Info) << "Growing buffers count from "
                    << buffers.size() << " to " << values.size();

            int extras = values.size() - buffers.size();
            for (int i=0 ; i < extras ; ++i) {
                buffers.push_back(ScrollingBuffer());
            }
        }

        for (int i=0 ; i < values.size() ; ++i) {
            buffers[i].add_point(sample.get_timestamp(), values[i]);
        }
    } else {
        LOG(Error) << "Unable to parse line: " << line;
    }
}

void PlotWidget::set_history_length(float seconds)
{
    history_length = seconds;
}

void PlotWidget::clear_points()
{
    for (ScrollingBuffer buffer : buffers) {
        buffer.erase();
    }
    buffers.clear();
}

