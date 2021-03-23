//
// Created by jinxd on 2021/3/21.
//

#ifndef SOURCE_CHANNEL_H
#define SOURCE_CHANNEL_H

#include <functional>

class Channel
{
public:
    Channel(int fd, int events);

    void handle_read_event();

    void handle_write_event();

private:
    int _fd;
    int _events;
    int _revents;
};


#endif //SOURCE_CHANNEL_H
