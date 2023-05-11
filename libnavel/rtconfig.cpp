#include <algorithm>
#include <string>
#include "rtconfig.hpp"

using namespace std::string_literals;
using namespace leapus::navelgazer::config;

arg_collision_error::arg_collision_error(const std::string &arg):
    arg_error("Commandline argument found claimed by another plugin: "s + arg){
}

Arg::Arg(const char *v, bool cl):
    value(v),
    claimed(cl){}

Configuration::Configuration(int argc, char *argv[]){
    m_args.resize(argc);
    std::copy(&argv[0], &argv[argc], m_args.begin());
}

Configuration::args_collection_type &Configuration::args(){ return m_args; }
const Configuration::args_collection_type &Configuration::args() const{ return m_args; }

