#ifndef SOURCE_CHANNEL_H
#define SOURCE_CHANNEL_H

#include <functional>

class Channel
{
public:
    Channel(int fd, int events);

    void set_fd(int fd);
    int fd() const;

    void set_revents(int events);
    int revents() const;

    void set_val(int val);
    int val() const;


private:
    int _fd;
    int _events;
    int _revents;

    int _val; // this member is for any use
};


#endif //SOURCE_CHANNEL_H
