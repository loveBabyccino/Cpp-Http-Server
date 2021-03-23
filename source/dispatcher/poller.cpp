//
// Created by jinxd on 2021/3/22.
//

#include "poller.h"

void Poller::add(int fd, int flags)
{
    control(fd, flags);
    epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &_event);
}

void Poller::modify(int fd, int flags)
{
    control(fd, flags);
    epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &_event);
}

void Poller::remove(int fd)
{
    epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, nullptr);
}

void Poller::wait(int time_out)
{

}

void Poller::control(int fd, int flags)
{
    int read_flag = flags & static_cast<int>(Event::READ);
    int write_flag = flags & static_cast<int>(Event::WRITE);
    int error_flag = flags & static_cast<int>( Event::ERROR);

    _event.data.fd = fd;
    _event.events = read_flag | write_flag | error_flag;
}
