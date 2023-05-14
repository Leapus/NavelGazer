#pragma once
/*
    A central place to put handling of informational, console,
    and debug notices
*/

#include <string>
#include "navelgazer/libnavel/pluginfwd.hpp"
#include "navelgazer/pluginapi/pluginlog.hpp"

namespace leapus::navelgazer::pluginapi{

class plugin_logger{
public:
    //informative notice issued by a plugin
    static void info(const leapus::navelgazer::interface &, const std::string &msg );
};

}
