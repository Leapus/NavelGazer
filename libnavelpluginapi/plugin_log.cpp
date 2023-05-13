#include <iostream>
#include "plugin.hpp"
#include "log.hpp"
#include "navelgazer/pluginapi/pluginlog.hpp"

using namespace std;
using namespace leapus::navelgazer;

void pluginapi::plugin_logger::info(const leapus::navelgazer::interface &iface, const std::string &msg){
    log::info(iface.interface_name() + ": " + msg);
}
