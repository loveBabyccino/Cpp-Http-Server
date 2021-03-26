#ifndef SOURCE_CHANNEL_H
#define SOURCE_CHANNEL_H

#include "noncopyable.h"

#include <functional>

class Channel : NonCopyable
{
    using EventCallBack = std::function<void()>;

public:
    Channel(int fd, int events = 0, int knownEvents = 0);

    int fd() const;

    void setKnownEvents(int events);
    int knownEvents() const;

    void setExpectedEvents(int events);
    int expectedEvents() const;

    void handleReadEvent();

    void handleWriteEvent();

private:
    int _fd;
    int _expected_events;
    int _knownEvents;

    EventCallBack _read_call_back;
    EventCallBack _write_call_back;
};


#endif //SOURCE_CHANNEL_H
