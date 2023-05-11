#pragma once
#include <stdexcept>

namespace leapus::navelgazer{

//Base class for all application errors
class navel_error:public std::runtime_error{
public:
    using runtime_error::runtime_error;
};

}

