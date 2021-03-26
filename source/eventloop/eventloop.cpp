#include "eventloop.h"
#include "dispatcher.h"
#include "channel.h"

#include <cassert>

EventLoop::EventLoop() :
    _thread_id(std::this_thread::get_id())
{

}

void EventLoop::thread_validate()
{
    assert(("thread violation", _thread_id != std::this_thread::get_id()));
}

void EventLoop::init()
{
    thread_validate();

    if (_inited == true)
        return;

    auto shared_this = shared_from_this();
    _dispatcher = std::make_shared<Dispatcher>(shared_this);
    _inited = true;
}

void EventLoop::run()
{
    assert(("event loop has been disturbed", _running == false));

    init();

    _channels.clear();

    while (_running == true)
    {
        _dispatcher->epoll(_channels);
    }
}

void EventLoop::stop()
{
    _running = false;
}

EventLoop::ObservedDispatcher EventLoop::dispatcher()
{
    return _dispatcher;
}


