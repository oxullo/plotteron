#include <Mahi/Gui.hpp>
#include <Mahi/Util/Logging/Log.hpp>

#include "plotteronapp.hpp"

using namespace mahi::util;

int main(int argc, char const *argv[])
{    
    mahi::gui::Application::Config config;

    LOG(Info) << "Plotteron starting up";

    config.title     = "Plotteron";
    config.width     = 800;
    config.height    = 600;
//    config.resizable = false;
    config.msaa      = true;
    config.center    = true;
    // config.decorated = false;

    PlotteronApp app(config);
    app.run();

    return 0;
}
