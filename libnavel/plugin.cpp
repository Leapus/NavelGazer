#include <string>
#include "plugin.hpp"
#include "log.hpp"

using namespace std::string_literals;
using namespace leapus::navelgazer;

const plugin_spec leapus::navelgazer::null_plugin_spec={};

bool operator!(const leapus::navelgazer::plugin_spec &ps){ 
    return !(ps==null_plugin_spec);
 }

plugin::plugin(const std::filesystem::path &path):
    m_library(path){

    plugin_dependencies_fptr depfp;
    m_library.get_symbol_static("plugin_name_f", m_name_fptr);
    m_library.get_symbol_static("plugin_dependencies_f", depfp);
    m_library.get_symbol_static("plugin_init", m_init_fptr);
    m_library.get_symbol_static("plugin_shutdown", m_shutdown_fptr);

    auto f=m_library.get_symbol_static<plugin_interface_fptr>("plugin_interface");
    m_iface=(*f)();
}

std::string plugin::name() const{
    return (*m_name_fptr)();
}

void plugin::init(){
    (*m_init_fptr)();
    m_running=true;
}

void plugin::shutdown(){
    m_running=false;
    (*m_shutdown_fptr)();
}

plugin_spec *plugin::dependencies() const{
    return m_deps;
}

bool plugin::running() const{
    return m_running;
}

void plugin_registry::path(const std::filesystem::path &p){
    m_dirpath=p;
}

void plugin_registry::load(const std::filesystem::path &name){
    auto path=m_dirpath;
    path+=name;
    plugin *pl=new plugin{path};

    m_by_guid[pl->iface()->interface_guid()]=pl;
    //m_by_name[pl->iface()->interface_name()]=pl;
    m_by_service.insert( { pl->iface()->interface_name(), pl } );
}

void plugin_registry::scan(){
    for( const auto &ent : std::filesystem::directory_iterator{m_dirpath} ){
        if(ent.is_regular_file())
            load(ent);
    }
}

plugin &plugin_registry::operator[](guid_type guid) const{
    return *m_by_guid.at(guid);
}

plugin_registry::by_name_const_iterator plugin_registry::operator[](const std::string &name) const{
    return m_by_service.find(name);
}

std::string plugin_spec::to_string() const{
    return "GUID: "s + std::to_string(guid) + ", Service: "s + service;
}

plugin &plugin_registry::operator[](const plugin_spec &sp) const{
    auto it = m_by_guid.find(sp.guid);
    if(it != m_by_guid.end())
        return *it->second;
    
    auto it2 = m_by_service.find(sp.service);
    if(it2 != m_by_service.end())
        return *it2->second;
    else
        throw plugin_missing("Plugin missing: "s + sp.to_string());
}

void plugin_registry::run(const plugin_spec &spec){
    recursive_init(spec);
}

void plugin_registry::init_deps(plugin &pl){
    for(auto p=pl.dependencies();p;++p){        
        recursive_init(*p);
    }
}

void plugin_registry::recursive_init(const plugin_spec &spec){
    auto &pl=(*this)[spec];

    if(!pl.running()){
        init_deps(pl);
        //leapus::navelgazer::pluginapi::logger::info("starting plugin: "s + pl.name());
        pl.init();
    }
}

