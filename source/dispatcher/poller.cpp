#include "poller.h"

#include <cassert>
#include <cstdlib>

Poller::Poller(int max_events)
{
    _epoll_fd = epoll_create(1);
    assert(("epoll_created error", _epoll_fd == -1));

    _event = epoll_event();
    auto* event_list = static_cast<epoll_event*>(calloc(max_events, sizeof(_event)));
}

void Poller::add(int fd, int flags)
{
    control(fd, flags);
    epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &_event);
}

void Poller::modify(int fd, int flags)
{
    control(fd, flags);
    epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &_event);
}

void Poller::remove(int fd)
{
    epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, nullptr);
}


void Poller::control(int fd, int flags)
{
    int read_flag = flags & static_cast<int>(Event::READ);
    int write_flag = flags & static_cast<int>(Event::WRITE);
    int error_flag = flags & static_cast<int>( Event::ERROR);

    _event.data.fd = fd;
    _event.events = read_flag | write_flag | error_flag;
}

int Poller::wait(int max_events, int time_out)
{
   return epoll_wait(_epoll_fd, _events, max_events, time_out);
}


