#ifndef SOURCE_EVENTLOOP_H
#define SOURCE_EVENTLOOP_H

#include "noncopyable.h"

#include <thread>
#include <atomic>
#include <memory>
#include <vector>


using std::enable_shared_from_this;

class Channel;
class Dispatcher;


class EventLoop : NonCopyable, enable_shared_from_this<EventLoop>
{
public:
    using InterestedChannelList = std::vector<Channel*>;


private:
    using ObservedDispatcher = std::shared_ptr<Dispatcher>;
    using ThreadID = std::thread::id;
    using AtomicFlag = std::atomic_bool;


public:
    EventLoop();

    ObservedDispatcher dispatcher();

    void run();

    void stop();


private:
    void init();

    void thread_validate();


private:
    ObservedDispatcher _dispatcher;
    InterestedChannelList _channels;
    ThreadID _thread_id;
    AtomicFlag _running {false };
    AtomicFlag _inited { false };
};


#endif
