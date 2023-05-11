#pragma once

/*
    A central place to put handling of informational, console,
    and debug notices
*/

#include <string>
#include "pluginfwd.hpp"
#include "log.hpp"

namespace leapus::navelgazer::pluginapi{

class logger{
public:
    //informative notice issued by a plugin
    static void info(const leapus::navelgazer::interface &, const std::string &msg );
};

}
