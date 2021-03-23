#include "dispatcher.h"
#include "channel.h"

#include <sys/epoll.h>
#include <sys/eventfd.h>

Dispatcher::Dispatcher(EventLoop *event_loop) :
    _loop(event_loop)
{
    _epoll_fd = epoll_create(1);

    _epoll_event_list = static_cast<epoll_event*>(calloc(_max_events, sizeof(epoll_event)));
}

void Dispatcher::poll(InterestedChannelList* interested_channels)
{
    struct epoll_event event = {};

    auto ready = epoll_wait(_event_fd, _epoll_event_list, _max_events, -1);

    for (int i = 0; i < ready; ++i)
    {
        if (_epoll_event_list[i].data.fd == _event_fd)
        {
            uint64_t fd = -1;
            eventfd_read(_event_fd, &fd);
            add_channel(fd, 1, 1, 0);
        }
        else
        {

        }
    }

}


void Dispatcher::remove_channel(Channel *channel)
{

}

void Dispatcher::update_channel(Channel *channel)
{

}

void Dispatcher::add_watched_fd(int fd, int events)
{
    epoll_event event = epoll_event();
    event.data.fd = fd;
    event.events = events;
    epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event);
    epoll_ctl(fd, EPOLL_CTL_ADD, fd, &event);
}

void Dispatcher::add_channel(int fd, int read, int write, int error)
{
    unsigned int read_mask = read == 0 ? 0 : EPOLLIN;
    unsigned int write_mask = write == 0 ? 0 : EPOLLOUT;
    unsigned int error_mask = error == 0 ? 0 : EPOLLHUP | EPOLLERR;

    auto channel = new Channel(fd, read_mask | write_mask | error_mask | EPOLLET);

    _channel_map[fd] = channel;
}

Dispatcher::Channels Dispatcher::find_active_channels() const
{
    return Dispatcher::Channels();
}


