#include <string>
#include "server_rtconfig.hpp"

using namespace leapus::navelgazer::config;
using namespace leapus::navelgazer;

std::string ServiceConfig::app_name() const{
    return app_name_str;
}

version_type ServiceConfig::version() const{
    return version_value;
}
