#ifndef SOURCE_POLLER_H
#define SOURCE_POLLER_H

#include <sys/epoll.h>
#include <map>

class Channel;

enum class Event
{
    READ = 1,
    WRITE = 2,
    ERROR = 4
};

struct PollerItem
{
    PollerItem() = default;
    PollerItem(int fd, int events) : _fd(fd), _events(events) {}
    int _fd { -1 };
    int _events { 0 };
    int _revents { 0 };
};

class Poller
{
public:
    using Poller_Item_List = std::map<int, PollerItem>;

private:
    using Epoll_Event_List = epoll_event*;
    using Epoll_Event = epoll_event;

public:
    Poller(int max_events);
    Poller(const Poller&) = delete;
    Poller& operator=(const Poller&) = delete;

    void add(int fd, int events);

    void modify(int fd, int events);

    void remove(int fd);

    int wait(Poller_Item_List& poller_items, int max_events = 128, int time_out = -1);

private:
    void control(int fd, int events);

private:
    int _epoll_fd { -1 };
    Epoll_Event _event{};
    Epoll_Event_List _events { nullptr } ;
    Poller_Item_List _poller_items;
};


#endif
