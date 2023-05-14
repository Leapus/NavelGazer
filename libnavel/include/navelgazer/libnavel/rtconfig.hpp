#pragma once

/*
    The runtime configuration state of the application,
    including the command-line and any configuration files
*/

#include <vector>
#include <string>
#include "types.hpp"
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

//Thrown when an expected argument is absent
class arg_missing_error:public arg_error{
public:
    using arg_error::arg_error;
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
    using args_const_iterator_type = args_collection_type::const_iterator;

private:
    args_collection_type m_args;

public:
    Configuration(int argc, char *argv[]);
    void demand_next(args_const_iterator_type &it);

    virtual args_collection_type &args();
    virtual const args_collection_type &args() const;
    virtual version_type version() const = 0;
    virtual std::string app_name() const = 0;
};

}

