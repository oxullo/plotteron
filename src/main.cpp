#include <Mahi/Gui.hpp>
#include <Mahi/Util/Logging/Log.hpp>

#include "app.hpp"

using namespace mahi::util;

int main(int argc, char const *argv[])
{    
    mahi::gui::Application::Config config;

    LOG(Info) << "Plotteron starting up";

    config.title     = "Plotteron";
    config.width     = 1600;
    config.height    = 1000;
//    config.resizable = false;
    config.msaa      = true;
    config.center    = true;
    // config.decorated = false;

    App app(config);
    app.run();

    return 0;
}
