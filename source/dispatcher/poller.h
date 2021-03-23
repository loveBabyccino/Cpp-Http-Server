#ifndef SOURCE_POLLER_H
#define SOURCE_POLLER_H

#include <sys/epoll.h>
#include <vector>

class Channel;

enum class Event
{
    READ = 1,
    WRITE = 2,
    ERROR = 4
};

class Poller
{
    using EpollEvent = epoll_event;
    using EpollEventList = epoll_event*;
    using InterestedChannels = std::vector<Channel*>;

public:
    Poller(const Poller&) = delete;
    Poller& operator=(const Poller&) = delete;

    Poller(Poller&&) = delete;
    Poller& operator=(Poller&&) = delete;

    void add(int fd, int flags);

    void modify(int fd, int flags);

    void remove(int fd);

    void wait(InterestedChannels& channels, int time_out = -1);

private:
    void control(int fd, int flags);

private:
    int _epoll_fd { -1 };
    EpollEvent _event;
    EpollEventList _events { nullptr } ;
};


#endif
