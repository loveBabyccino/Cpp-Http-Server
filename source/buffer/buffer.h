//
// Created by jinxd on 2021/3/18.
//

#ifndef HTTP_SERVER_BUFFER_H
#define HTTP_SERVER_BUFFER_H

#include <vector>
#include <string>

class Buffer
{
public:

    /*
     *  given a specific initial capacity
     * */
    explicit Buffer(size_t capacity = 2048);

    /*
     *  return the current read index
     * */
    unsigned int read_index() const;

    /*
     *  return the current write index
     * */
    unsigned int write_index() const;

    /*
     *  return the entire capacity
     * */
    size_t capacity() const;

    /*
     *  return size used already
     * */
    size_t size() const;

    /*
     *  return available space for reads
     * */
    size_t readable_size() const;

    /*
     *  return available space for writes
     * */
    size_t writable_size() const;

    /*
     *  write bytes into the buffer
     * */
    bool write(const std::string& bytes);

    /*
     *  read bytes from the buffer
     * */
    std::string read(unsigned int amount);

    /*
     *  discard the bytes already read
     *  be aware this function involves memory copy
     * */
    void refresh();

    /*
     *  empty the buffer
     * */
    void clear();

    /*
     * reposition the read index
     * NOTE: this function can be used to seek the buffer,
     * pos should be always positive and
     * read index should always not be greater than the write index,
     * otherwise returns false
     * */
    bool seek(int pos);

private:
    std::vector<char> _buffer;

    size_t _size {0};
    size_t _internal_capacity { 0 };
    size_t _capacity { 0 };

    unsigned int _write_index {0};
    unsigned int _read_index {0};
};


#endif //HTTP_SERVER_BUFFER_H
