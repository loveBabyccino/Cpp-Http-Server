#include "dispatcher.h"
#include "channel.h"
#include "poller.h"

#include <sys/eventfd.h>

Dispatcher::Dispatcher(EventLoop* event_loop, int max_events) :
    _loop(event_loop),
    _max_events(max_events),
    _poller(new Poller(max_events))
{

}

void Dispatcher::set_max_events(int n)
{
    _max_events = n;
}

void Dispatcher::poll(InterestedChannelList* interested_channels)
{
    auto ready = _poller->wait(_max_events);
    if (ready >0)
    {

    }
    else if (ready == 0)
    {

    }
    else
    {

    }

}


void Dispatcher::remove_channel(Channel *channel)
{
    if (channel == nullptr)
        return;


}

void Dispatcher::update_channel(Channel *channel)
{
    if (channel == nullptr)
        return;

    auto fd = channel->fd();

    if (_channel_map.count(channel->fd()) == 0)
    {
        channel->set_revents(0);
        _interested__fds.push_back(fd);
        _channel_map[fd] = channel;
        _poller->add(fd, channel->revents());
    }
    else
    {
        channel->set_revents(0);
        _poller->modify(fd, channel->revents());
    }
}




Dispatcher::Channels Dispatcher::find_active_channels() const
{
    return Dispatcher::Channels();
}


