#include "concurrent.hpp"


using namespace leapus::concurrent;


critical_section::lock_type critical_section::lock(){
    return lock_type{m_mutex};
}

