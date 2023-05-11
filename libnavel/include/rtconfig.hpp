#pragma once

/*
    The runtime configuration state of the application,
    including the command-line and any configuration files
*/

#include <vector>
#include <string>
#include "exception.hpp"

namespace leapus::navelgazer::config{

class arg_error:public navel_error{
public:
    using navel_error::navel_error;
};

class arg_collision_error:public arg_error{
public:
    arg_collision_error(const std::string &arg);
};

//Keep track of whether each argument has been claimed in order to detect
//extraneous arguments, or argument name collisions amongst plugins
struct Arg{
    Arg(const char *v="", bool cl=false);
    std::string value;
    bool claimed=false;
};

//Derive from this base class for client and server
class Configuration{
public:
    using args_collection_type = std::vector<Arg>;

private:
    args_collection_type m_args;

public:
    Configuration(int argc, char *argv[]);
    args_collection_type &args();
    const args_collection_type &args() const;
};

}

