#pragma once

/*
* Multithreading related stuff
*
*/

#include <mutex>
#include <deque>
#include <condition_variable>

namespace leapus::concurrent{

//A critical section which can only be executed by zero or one threads at any given time
//Meant to be instantiated as a static local, and then called to return an exclusive scoped lock
class critical_section{
    using mutex_type=std::mutex;
    mutex_type m_mutex;

public:
    using lock_type=std::unique_lock<mutex_type>;
    lock_type lock();
};


//Concurrent message queue
template<typename T, typename M=std::mutex, typename L=std::unique_lock<M>>
class message_queue{
public:
    using value_type=T;
    using mutex_type=M;
    using lock_type=L;

private:
    using container_type=std::deque<value_type>;

    container_type m_queue;
    mutex_type m_mutex;
    std::condition_variable_any m_cond;

public:
    void push(value_type &&msg){
        {
            lock_type lock{m_mutex};
            m_queue.push_back(std::move(msg));
        }
        m_cond.notify_all();
    }

    void push(const value_type &msg){
        {
            lock_type lock{m_mutex};
            m_queue.push_back(msg);
        }
        m_cond.notify_all();
    }

    //Blocks and waits if the queue is empty
    value_type pop(){
        lock_type lock{m_mutex};
        m_cond.wait(lock, [this]{return !m_queue.empty();});
        auto result=std::move(m_queue.front());
        m_queue.pop_front();
        return result;
    }

};



}