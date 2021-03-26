
#ifndef SOURCE_SOCKET_H
#define SOURCE_SOCKET_H

#include "noncopyable.h"

#include <string>
//#include <netinet/in.h>
#include <arpa/inet.h>


class SockAddress
{
public:
    SockAddress();
    explicit SockAddress(const char* ip, int port);
    explicit SockAddress(const sockaddr_in& addr);

    void setIP(const char* ip);
    std::string ip() const;

    void setPort(int port);
    int port() const;

    sockaddr_in sockAddress() const;

private:
    int _port { -1 };
    std::string _ip;
    sockaddr_in _addr {};
};


class Socket : NonCopyable
{
public:
    explicit Socket(bool nonblocking);

    void setAddressReusable() const;

    void setPotReusable() const;

    void setKeepAlive() const;

    void bind(const SockAddress& sock_addr) const;

    void listen(int backlog) const;

    void accept(SockAddress& sock_addr) const;

    int fd() const;

    bool nonblocking() const;

private:
    void create();

private:
    int _fd { -1 };
    bool _nonblocking { false };
};


#endif
