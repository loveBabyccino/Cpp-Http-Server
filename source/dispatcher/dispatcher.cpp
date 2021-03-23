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

void Dispatcher::poll(Interested_Channel_List* interested_channels)
{
    Poller::Poller_Item_List poller_items;

    auto ready = _poller->wait(poller_items, _max_events);
    if (ready >0)
    {

    }
    else if (ready == 0)
    {
        // log here
    }
    else
    {

    }

}


void Dispatcher::remove_channel(Channel *channel)
{
    if (channel == nullptr)
        return;

    auto fd = channel->fd();
    _channel_map.erase(fd);
    _interested_fds.remove(fd);
    _poller->remove(fd);
}

void Dispatcher::update_channel(Channel *channel)
{
    if (channel == nullptr)
        return;

    auto fd = channel->fd();

    if (_channel_map.count(channel->fd()) == 0)
    {
        channel->set_revents(0);
        _interested_fds.push_front(fd);
        _channel_map[fd] = channel;
        _poller->add(fd, channel->revents());
    }
    else
    {
        channel->set_revents(0);
        _poller->modify(fd, channel->revents());
    }
}




//Dispatcher::Channels Dispatcher::find_active_channels() const
//{
//    return Dispatcher::Channels();
//}


