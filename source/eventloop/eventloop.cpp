#include "eventloop.h"
#include "dispatcher.h"

#include <cassert>

EventLoop::EventLoop(Dispatcher *dispatcher) :
    _dispatcher(dispatcher),
    _thread_id(std::this_thread::get_id())
{

}

void EventLoop::validate_thread()
{
    assert(("thread violation", _thread_id == std::this_thread::get_id()));
}

void EventLoop::run()
{
    validate_thread();

    if (_running == true)
        return;

    while (_running == true)
    {
        _dispatcher->poll();
    }
}

void EventLoop::stop()
{
    _running = false;
}
