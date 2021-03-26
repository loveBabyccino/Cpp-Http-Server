#include "dispatcher.h"
#include "channel.h"

#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <cassert>


Dispatcher::Dispatcher(ObserverdEventLoop event_loop, int max_events) :
    _event_loop(std::move(event_loop)),
    _max_events(max_events),
    _epoll_fd(epoll_create(1)),
    _epoll_event_list(max_events)
{

}

void Dispatcher::eventLoopValidate()
{
    assert(("no event loop exists", _event_loop.lock() != nullptr));
}

void Dispatcher::setMaxEvents(int n)
{
    _max_events = n;
}

void Dispatcher::updateChannel(Channel *channel)
{
    eventLoopValidate();

    if (channel == nullptr)
        return;

    auto fd = channel->fd();

    struct epoll_event event;
    event.data.fd = fd;
    event.events = channel->expectedEvents();
    event.data.ptr = channel;

    if (_channel_map.count(channel->fd()) == 0)
    {
        _channel_map[fd] = channel;
        epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event);
    }
    else
    {
        _channel_map[fd] = channel;
        epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &event);
    }
}

void Dispatcher::removeChannel(Channel *channel)
{
    eventLoopValidate();

    if (channel == nullptr)
        return;

    auto fd = channel->fd();
    _channel_map.erase(fd);
    epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
}

void Dispatcher::epoll(InterestedChannelList& interested_channels)
{
    eventLoopValidate();

    auto ready = epoll_wait(_epoll_fd, &(*_epoll_event_list.begin()), _epoll_event_list.size(), -1);

    if (ready >0)
    {
        findActiveChannels(ready, interested_channels);
    }
    else if (ready == 0)
    {
        // log here
    }
    else
    {

    }

}

void Dispatcher::findActiveChannels(int ready, Dispatcher::InterestedChannelList& interested_channels)
{
    for (int i = 0; i < ready; ++i)
    {
        auto channel = static_cast<Channel*>(_epoll_event_list[i].data.ptr);
        auto fd = channel->fd();
        auto it = _channel_map.find(fd);
        assert(("channel not exist", it != _channel_map.end()));
        assert(("invalid channel", it->second == channel));
        interested_channels.push_back(channel);
    }
}

Dispatcher::EventType Dispatcher::eventType(int type) const
{
    EventType eventType;
    switch (type)
    {
        case EPOLLIN:
            eventType = EventType::Read;
            break;
        case EPOLLOUT:
            eventType = EventType::Write;
            break;
        default:
            eventType = EventType::Error;
    }
    return eventType;
}





