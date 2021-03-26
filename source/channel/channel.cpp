#include "channel.h"

Channel::Channel(int fd, int events, int knownEvents) :
    _fd(fd),
    _expected_events(events),
    _knownEvents(knownEvents)
{

}

int Channel::fd() const
{
    return _fd;
}

int Channel::knownEvents() const
{
    return _knownEvents;
}

void Channel::setKnownEvents(int events)
{
    _knownEvents = events;
}

void Channel::setExpectedEvents(int events)
{
    _expected_events = events;
}

int Channel::expectedEvents() const
{
    return _expected_events;
}

void Channel::handleReadEvent()
{
    _read_call_back();
}

void Channel::handleWriteEvent()
{
    _write_call_back();
}



