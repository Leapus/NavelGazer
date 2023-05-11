#pragma once

/*
* Multithreading related stuff
*
*/

#include <mutex>

namespace leapus::navelgazer{

//A critical section which can only be executed by zero or one threads at any given time
//Meant to be instantiated as a static local, and then called to return an exclusive scoped lock
class critical_section{
    using mutex_type=std::mutex;
    mutex_type m_mutex;

public:
    using lock_type=std::unique_lock<mutex_type>;
    lock_type lock();
};

}