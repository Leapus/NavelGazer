#pragma once

/*
*
* Define a really simple dynamic library loader which will have different
* implementations depending on whether it's Windows, Linux, or maybe something else
*
*/

#include <stdexcept>
#include <string>
#include <filesystem>

//A stub that pulls in implementation details
#include "libloader_impl.hpp"

namespace leapus{

class dynamic_library_exception:public std::runtime_error{
    using runtime_error::runtime_error;
};

class dynamic_library:protected dynamic_library_impl{
public:
    dynamic_library( const std::filesystem::path &path );
    ~dynamic_library();
    void *get_symbol(const std::string &name);

    template<typename T>
    T *get_symbol_static(const std::string &name){
        return static_cast<T *>(get_symbol(name));
    }

    //Deduce the target type a bit more easily
    template<typename T>
    void get_symbol_static(const std::string &name, T &v){
        v=*get_symbol_static<T>(name);
    }

    template<typename T>
    T *get_symbol_dynamic(const std::string &name){
        return dynamic_cast<T *>(get_symbol(name));
    }

    template<typename T>
    void get_symbol_dynamic(const std::string &name, T &v){
        v = *get_symbol_dynamic<T>(name);
    }
};
}
