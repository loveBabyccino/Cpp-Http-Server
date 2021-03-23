#include "channel.h"

Channel::Channel(int fd, int events) :
    _fd(fd), _events(events)
{

}

void Channel::set_fd(int fd)
{
    _fd = fd;
}

int Channel::fd() const
{
    return _fd;
}

int Channel::revents() const
{
    return _revents;
}

void Channel::set_revents(int events)
{
    _revents = events;
}

void Channel::set_val(int val)
{
    _val = val;
}

int Channel::val() const
{
    return _val;
}


