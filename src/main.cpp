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
