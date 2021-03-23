#ifndef SOURCE_DISPATCHER_H
#define SOURCE_DISPATCHER_H

#include <unordered_map>
#include <vector>

class epoll_event;

class Channel;
class EventLoop;

class Dispatcher
{
    using ChannelMap = std::unordered_map<int, Channel*>;
    using InterestedChannelList = std::vector<Channel>;

    using WatchedFDs = std::vector<int>;

public:

    explicit Dispatcher(EventLoop* event_loop);

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

public:
    void poll(InterestedChannelList* interested_channels);

    void remove_channel(Channel* channel);

    void update_channel(Channel* channel);

    void find_active_channels();

private:
    void add_watched_fd(int fd, int events);

    void add_channel(int fd, int read, int write, int error);

private:
    InterestedChannelList* _interested_channels { nullptr };

    EventLoop* _loop { nullptr };
    ChannelMap _channel_map;
    WatchedFDs _fds;

    int _epoll_fd;
    epoll_event* _epoll_event_list { nullptr };

    const int _max_events { 128 };
};


#endif //SOURCE_DISPATCHER_H
