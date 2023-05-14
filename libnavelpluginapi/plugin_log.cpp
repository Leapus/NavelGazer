#include <iostream>
#include "navelgazer/libnavel/plugin.hpp"
#include "navelgazer/libnavel/log.hpp"
#include "navelgazer/pluginapi/pluginlog.hpp"

using namespace std;
using namespace leapus::navelgazer;

void pluginapi::plugin_logger::info(const leapus::navelgazer::interface &iface, const std::string &msg){
    log::info(iface.interface_name() + ": " + msg);
}
