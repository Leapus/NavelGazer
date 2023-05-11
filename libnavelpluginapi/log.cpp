#include <iostream>
#include "concurrent.hpp"
#include "plugin.hpp"
#include "log.hpp"

using namespace std;
using namespace leapus::navelgazer::pluginapi;

void logger::info(const leapus::navelgazer::interface &iface, const std::string &msg){
    static critical_section crit;
    auto lock=crit.lock();
    cout << iface.interface_name() << ": " << msg << endl;
}
