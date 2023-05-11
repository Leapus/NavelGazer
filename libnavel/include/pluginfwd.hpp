#pragma once

namespace leapus::navelgazer{

class plugin;
class plugin_registry;

//A plugin dependency
//A 0 GUID means we will settle for any matching service by name
//An empty service means we demand a specific GUID
//Both empty/zero is a null spec that specifies nothing
struct plugin_spec{
    guid_type guid={0};
    std::string service={};
    std::string to_string() const;
} null_plugin_spec;

}
