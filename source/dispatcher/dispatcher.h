#ifndef SOURCE_DISPATCHER_H
#define SOURCE_DISPATCHER_H

#include <map>
#include <vector>
#include <forward_list>

class Poller;
class Channel;
class EventLoop;


class Dispatcher
{
    using Channel_Map = std::map<int, Channel*>;
    using Interested_Channel_List = std::vector<Channel>;
    using Interested_FD_List = std::forward_list<int>;

public:
    explicit Dispatcher(EventLoop* event_loop, int max_events = 128);

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

public:
    void poll(Interested_Channel_List* interested_channels);

    void set_max_events(int n);

    void update_channel(Channel* channel);

    void remove_channel(Channel* channel);

    void find_active_channels();


private:
    Poller* _poller { nullptr };
    EventLoop* _loop { nullptr };

    Channel_Map _channel_map;
    Interested_Channel_List* _interested_channels { nullptr };
    Interested_FD_List _interested_fds;

    int _max_events { 0 };
};


#endif //SOURCE_DISPATCHER_H
