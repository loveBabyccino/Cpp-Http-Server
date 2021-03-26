#ifndef SOURCE_DISPATCHER_H
#define SOURCE_DISPATCHER_H

#include "noncopyable.h"

#include <map>
#include <memory>
#include <vector>


class Channel;
class EventLoop;
class epoll_event;

class Dispatcher : NonCopyable
{
    using ObserverdEventLoop = std::weak_ptr<EventLoop>;
    using ChannelMap = std::map<int, Channel*>;
    using InterestedChannelList = std::vector<Channel*>;
    using EpollEventList = std::vector<epoll_event>;

public:
    enum class EventType
    {
        Read,
        Write,
        Error
    };

public:
    explicit Dispatcher(ObserverdEventLoop event_loop, int max_events = 128);

    void epoll(InterestedChannelList& interested_channels);

    void setMaxEvents(int n);

    void updateChannel(Channel* channel);

    void removeChannel(Channel* channel);

    EventType eventType(int type) const;

private:
    void eventLoopValidate();

    void findActiveChannels(int ready, InterestedChannelList& interested_channels);

private:
    int _epoll_fd { -1 };

    EpollEventList _epoll_event_list;

    ObserverdEventLoop _event_loop;

    ChannelMap _channel_map;

    int _max_events { 0 };
};


#endif //SOURCE_DISPATCHER_H
