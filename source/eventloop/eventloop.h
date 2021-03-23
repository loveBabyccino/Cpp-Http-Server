#ifndef SOURCE_EVENTLOOP_H
#define SOURCE_EVENTLOOP_H

#include <thread>
#include <atomic>
#include <vector>

class Channel;
class Dispatcher;

class EventLoop
{
    using InterestedChannelList = std::vector<Channel>;
    using ThreadID = std::thread::id;
    using RunningFlag = std::atomic_bool;

public:
    explicit EventLoop(Dispatcher* dispatcher);

    EventLoop(const EventLoop&) = delete;
    EventLoop& operator=(const EventLoop&) = delete;

    void run();
    void stop();

private:
    void validate_thread();

private:
    Dispatcher* _dispatcher { nullptr };
    InterestedChannelList _channels;
    ThreadID _thread_id;
    RunningFlag _running {false };
};


#endif
