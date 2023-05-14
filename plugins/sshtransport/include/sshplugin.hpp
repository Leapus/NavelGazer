#pragma once
#include "navelgazer/pluginapi/pluginapi.hpp"
#include "navelgazer/pluginapi/iface_transport.hpp"

namespace leapus::navelgazer::sshtransport{

class SSHConnection:public Connection{
public:
    void disconnect() override;
    void read(char *inbuf, size_t ct) override;
    void write(const char *, size_t ct) override;
    bool connected() const override;
};

class plugin_sshtransport:public iface_transport{
public:
    std::string interface_name() const override{
        return "SSH Transport";
    }

    guid_type interface_guid() const override{
        return 1;
    }

    version_type interface_version() const override{
        return {0,1};
    }

    Connection *connect(const std::string &addr) override;
    Connection *listen() override;
};

}
