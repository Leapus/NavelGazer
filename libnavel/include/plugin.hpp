#pragma once

#include <string>
#include <filesystem>
#include <map>
#include "exception.hpp"
#include "libloader.hpp"
#include "types.hpp"
#include "pluginfwd.hpp"

namespace leapus::navelgazer{

//There will be some root plugin for an application
//And then that plugin will define a number of other service strings that it expects to find
//in order to accomplish whatever it does. Contrib or user-defined extension names can be
//prefixed with "X" to avoid name collisions affecting compatibility with the main release.

//The base class for an object representing the interface
//into a plugin.
class interface{
public:
    virtual std::string interface_name() const=0;
    virtual guid_type interface_guid() const=0;
    virtual version_type interface_version() const=0;
    virtual std::string interface_service() const=0;
};

using plugin_name_fptr = const char *(*)();
using plugin_dependencies_fptr = plugin_spec *(*)();    //0-terminated string of dependencies
using plugin_init_fptr = void (*)();                    //Entry point called when the plugin is loaded, but after dependencies are met
using plugin_shutdown_fptr = void (*)();                //Shutdown routine called when the plugin is unloaded
using plugin_interface_fptr = interface *(*)();

class plugin{
    dynamic_library m_library;
    //plugin_dependencies_fptr m_deps;
    plugin_name_fptr m_name_fptr;
    plugin_init_fptr m_init_fptr;
    plugin_shutdown_fptr m_shutdown_fptr;
    //plugin_interface_fptr m_interface_fptr;
    plugin_spec *m_deps=nullptr;
    interface *m_iface=nullptr;
    bool m_running=false;

public:
    plugin( const std::filesystem::path &path );
    virtual ~plugin();

    std::string name() const;
    void init();
    void shutdown();

    template<typename T=interface>
    T *iface(){
        return dynamic_cast<T*>(m_iface);
    }

    plugin_spec *dependencies() const;
    bool running() const;

};

class plugin_error:public navel_error{
public:
    using navel_error::navel_error;
 };

class plugin_missing:public plugin_error{

public:
    using plugin_error::plugin_error;
};

class plugin_registry{
    using guid_map_type=std::map<guid_type,plugin *>;
    using service_map_type=std::multimap<std::string,plugin *>;
    guid_map_type m_by_guid;
    service_map_type m_by_service;
    std::filesystem::path m_dirpath;

protected:
    void recursive_init(const plugin_spec &);
    void init_deps(plugin &pl);

public:
    using by_name_iterator=service_map_type::iterator;
    using by_name_const_iterator=service_map_type::const_iterator;

    static plugin_registry &instance();
    void path(const std::filesystem::path &p);
    void scan();
    void load(const std::filesystem::path &name);
    void run(const plugin_spec &);
    void unload( guid_type id );

    plugin &operator[](guid_type guid) const;
    by_name_const_iterator operator[](const std::string &name) const;
    plugin &operator[](const plugin_spec &sp) const;
};

}
