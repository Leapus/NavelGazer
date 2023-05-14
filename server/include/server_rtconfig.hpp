#pragma once

#include <string>
#include "navelgazer/libnavel/rtconfig.hpp"

namespace leapus::navelgazer::config{

class ServiceConfig:public Configuration{

public:
    using Configuration::Configuration;

    static constexpr char app_name_str[]="navelserver";
    static constexpr version_type version_value={0, 1};

    version_type version() const override;
    std::string app_name() const override;
};

}
