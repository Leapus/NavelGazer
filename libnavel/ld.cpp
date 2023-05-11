#include <dlfcn.h>
#include <string>
#include "libloader.hpp"

using namespace std::string_literals;
using namespace leapus;

dynamic_library::dynamic_library( const std::filesystem::path &path ){
    m_handle=::dlopen( path.c_str(), RTLD_NOW |  RTLD_GLOBAL );
    if(m_handle == NULL)
        throw dynamic_library_exception( ::dlerror() );
}

dynamic_library::~dynamic_library(){
    ::dlclose(m_handle);
}

void *dynamic_library::get_symbol(const std::string &name){
    ::dlerror();    //This clears any previous error
    auto p=::dlsym(m_handle, ("_"s+name).c_str());
    auto err=::dlerror();
    if(p==NULL && err!=NULL)
        throw dynamic_library_exception(err);
    else
        return p;
}
