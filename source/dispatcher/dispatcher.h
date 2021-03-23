#ifndef SOURCE_DISPATCHER_H
#define SOURCE_DISPATCHER_H

#include <unordered_map>
#include <vector>

class Poller;
class Channel;
class EventLoop;


class Dispatcher
{
    using ChannelMap = std::unordered_map<int, Channel*>;
    using InterestedChannelList = std::vector<Channel>;
    using WatchedFDs = std::vector<int>;

public:
    explicit Dispatcher(EventLoop* event_loop, int max_events = 128);

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

public:
    void poll(InterestedChannelList* interested_channels);

    void set_max_events(int n);

    void update_channel(Channel* channel);

    void remove_channel(Channel* channel);

    void find_active_channels();


private:
    Poller* _poller { nullptr };
    EventLoop* _loop { nullptr };

    ChannelMap _channel_map;
    InterestedChannelList* _interested_channels { nullptr };
    WatchedFDs _interested__fds;

    int _max_events { 0 };
};


#endif //SOURCE_DISPATCHER_H
