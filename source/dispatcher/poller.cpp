#include "poller.h"

#include <cassert>
#include <cstdlib>


Poller::Poller(int max_events)
{
    _epoll_fd = epoll_create(1);
    assert(("epoll_created error", _epoll_fd > 0));

    _event = epoll_event();
    _events = static_cast<epoll_event*>(calloc(max_events, sizeof(_event)));
}

void Poller::add(int fd, int events)
{
    control(fd, events);
    epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &_event);
}

void Poller::modify(int fd, int events)
{
    control(fd, events);
    epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &_event);
}

void Poller::remove(int fd)
{
    epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
}


void Poller::control(int fd, int events)
{
    int read_flag = events & static_cast<int>(Event::READ);
    int write_flag = events & static_cast<int>(Event::WRITE);
    int error_flag = events & static_cast<int>( Event::ERROR);

    _event.data.fd = fd;
    _event.events = read_flag | write_flag | error_flag;
}

int Poller::wait(Poller_Item_List& poller_items, int max_events, int time_out)
{
   int epoll_ready = epoll_wait(_epoll_fd, _events, max_events, time_out);

   if (epoll_ready > 0)
   {
       PollerItem item;
       for (int i = 0; i < epoll_ready; ++i)
       {
           item._fd = _events->data.fd;
           item._knownEvents = _events->events;
           poller_items[item._fd] = item;
       }
   }

   return epoll_ready;
}


