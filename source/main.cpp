#include <iostream>

#include <sys/eventfd.h>

int main()
{
    int efd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);

    int ret = eventfd_write(efd, 100);
//    ret = eventfd_write(efd, 200);

    uint64_t val;
    ret = eventfd_read(efd, &val);
    ret = eventfd_read(efd, &val);

    return 0;
}
