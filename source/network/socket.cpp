#include "socket.h"

#include <sys/socket.h>
#include <cassert>
#include <fcntl.h>

/*
 *
 *  SockAddress
 *
 */

SockAddress::SockAddress()
{
    _addr.sin_family = AF_INET;
}

SockAddress::SockAddress(const char *ip, int port)
{
    _addr.sin_family = AF_INET;
    setIP(ip);
    setPort(port);
}

SockAddress::SockAddress(const sockaddr_in& addr)
{
    _addr = addr;

    char ip_str[INET_ADDRSTRLEN];
    _ip = inet_ntop(AF_INET, &_addr.sin_addr, ip_str, sizeof(ip_str));

    _port = ntohs(_addr.sin_port);
}

void SockAddress::setIP(const char* ip)
{
    inet_pton(AF_INET, ip, &_addr.sin_addr.s_addr);
    _ip = ip;
}

void SockAddress::setPort(int port)
{
    _addr.sin_port = htons(port);
    _port = port;
}

std::string SockAddress::ip() const
{
    return _ip;
}

int SockAddress::port() const
{
    return _port;
}

sockaddr_in SockAddress::sockAddress() const
{
    return _addr;
}


/*
 *
 *  Socket
 *
 */

Socket::Socket(bool nonblocking) :
    _nonblocking(nonblocking)
{
    create();
}

void Socket::create()
{
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(("failed to create a socket", _fd != -1));

    if (_nonblocking)
    {
        auto flags = (fcntl(_fd, F_GETFL) | O_NONBLOCK);
        auto success = fcntl(_fd, F_SETFL, flags);
        assert(("fcntl O_NONBLOCK error", success < 0));
    }
}

void Socket::setAddressReusable() const
{
    auto enable = 1;
    setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
}

void Socket::setPotReusable() const
{
    auto enable = 1;
    setsockopt(_fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable));
}

void Socket::setKeepAlive() const
{
    auto enable = 1;
    setsockopt(_fd, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));
}

void Socket::bind(const SockAddress& sock_addr) const
{
    auto local_sock_addr = sock_addr.sockAddress();
//    auto success = ::bind(_fd, (sockaddr*)(&sock), sizeof(sock));
    auto success = ::bind(_fd, reinterpret_cast<sockaddr*>(&local_sock_addr), sizeof(local_sock_addr));
    assert(("failed to bind a socket", success != -1));
}

void Socket::listen(int backlog) const
{
    auto success = ::listen(_fd, backlog);
    assert(("failed to listen on a socket", success != -1));
}

void Socket::accept(SockAddress& sock_addr) const
{
    auto peer_sock_addr = sock_addr.sockAddress();
    auto len = static_cast<socklen_t>(sizeof(peer_sock_addr));
    auto success = ::accept(_fd, reinterpret_cast<sockaddr*>(&peer_sock_addr), &len);
    assert(("failed to accept a new connection", success != -1));
}

int Socket::fd() const
{
    return _fd;
}

bool Socket::nonblocking() const
{
    return _nonblocking;
}






