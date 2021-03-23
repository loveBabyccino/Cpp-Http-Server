//
// Created by jinxd on 2021/3/21.
//

#include "channel.h"

Channel::Channel(int fd, int events) :
    _fd(fd), _events(events)
{

}

void Channel::handle_read_event()
{

}

void Channel::handle_write_event()
{

}
