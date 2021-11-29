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

#include <Mahi/Gui.hpp>
#include <Mahi/Util/Logging/Log.hpp>

#include "app.hpp"
#include "config.hpp"

using namespace mahi::util;

int main(int argc, char const *argv[])
{
    mahi::gui::Application::Config config;

    LOG(Info) << PROJECT_NAME << " v" << PROJECT_VER << " starting up";

    config.title     = PROJECT_NAME
            + std::string(" v") + std::string(PROJECT_VER);
    config.width     = 1600;
    config.height    = 1000;
    config.msaa      = true;
    config.center    = true;

    App app(config);
    app.run();

    return 0;
}
