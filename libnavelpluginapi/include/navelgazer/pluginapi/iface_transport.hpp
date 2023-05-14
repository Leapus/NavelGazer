#pragma once

#include <deque>
//#include ""
#include "pluginapi.hpp"

namespace leapus::navelgazer::sshtransport{

class transport_error:public plugin_error{
public:
    using plugin_error::plugin_error;
};

class Connection{
public:
    virtual inline ~Connection(){
        disconnect();
    }

    //Inline to avoid a warning, but you need to implement this
    virtual inline void disconnect(){}

    //These always complete the full buffer unless there's an error
    //So, there are no partial read/write semantics
    virtual void read(char *inbuf, size_t ct)=0;
    virtual void write(const char *, size_t ct)=0;
    virtual bool connected() const;

    inline operator bool() const{ return connected(); } //true if connected

    template<typename T>
    void write(const T &obj){
        write( static_cast<const char *>(&obj), sizeof(obj) );
    }

    template<typename T>
    void read(T &obj){
        read( static_cast<char *>(&obj), sizeof(obj) );
    }
};

class iface_transport:public interface{
public:
    using interface::interface;

    std::string interface_service() const override{
        return "TRANSPORT";
    }

    //Client-connect to server
    virtual Connection *connect(const std::string &addr)=0;

    //Listen as server for client connections
    virtual Connection *listen()=0;
};

}

