#pragma once

namespace leapus::navelgazer{

class plugin;
class plugin_registry;


class plugin_error:public navel_error{
public:
    using navel_error::navel_error;
 };

class plugin_missing:public plugin_error{

public:
    using plugin_error::plugin_error;
};

//A plugin dependency
//A 0 GUID means we will settle for any matching service by name
//An empty service means we demand a specific GUID
//Both empty/zero is a null spec that specifies nothing
extern const struct plugin_spec{
    bool operator==(const plugin_spec &) const=default;
    guid_type guid={0};
    std::string service={};
    std::string to_string() const;
} null_plugin_spec;

}

bool operator!(const leapus::navelgazer::plugin_spec &ps);
