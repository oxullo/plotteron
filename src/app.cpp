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

#include "app.hpp"

#include <iostream>


App::App(const Application::Config config) :
    mahi::gui::Application(config),
    device_widget(*this),
    plot_widget(*this),
    history_length(10)
{
    plot_widget.set_history_length(history_length);

    device_widget.on_point_acquired.connect(plot_widget, &PlotWidget::add_point);
    device_widget.on_connected.connect(plot_widget, &PlotWidget::clear_points);
}

void App::update()
{
    reposition_widgets();
    plot_widget.update();
    device_widget.update();
}

void App::reposition_widgets()
{
    ImVec2 viewport_pos = ImGui::GetMainViewport()->Pos;
    ImVec2 viewport_size = ImGui::GetMainViewport()->Size;

    device_widget.position = viewport_pos;
    device_widget.size = ImVec2(viewport_size.x, 50);

    plot_widget.position = ImVec2(viewport_pos.x, viewport_pos.y + 50);
    plot_widget.size = ImVec2(viewport_size.x, viewport_size.y - 50);
}
