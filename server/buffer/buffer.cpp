//
// Created by jinxd on 2021/3/18.
//

#include "buffer.h"

using std::vector;
using std::string;


Buffer::Buffer(size_t capacity) :
        _capacity(capacity),
        _internal_capacity(capacity),
        _buffer(vector<char>(capacity))
{

}

unsigned int Buffer::read_index() const
{
    return _read_index;
}

unsigned int Buffer::write_index() const
{
    return _write_index;
}

size_t Buffer::capacity() const
{
    return _capacity;
}

size_t Buffer::size() const
{
    return _size;
}

size_t Buffer::readable_size() const
{
    return _write_index - _read_index;
}

size_t Buffer::writable_size() const
{
    return _capacity - _write_index;
}

bool Buffer::write(const std::string& bytes)
{
    auto len = bytes.size();

    if (len > _capacity - _write_index)
        return false;

    std::copy(bytes.cbegin(), bytes.cend(), _buffer.begin() + _write_index);
    _write_index += len;

    return true;
}

std::string Buffer::read(unsigned int amount)
{
    if (amount == 0)
        return "";

    if (amount > _write_index  - _read_index)
        amount = _write_index  - _read_index;

    string output(amount, '\0');
    auto beg = output.begin();

    while (_read_index < _write_index)
    {
        *beg = _buffer[_read_index];
        ++_read_index;
        ++beg;
    }

    return output;
}

void Buffer::refresh()
{
    if (_read_index == 0)
        return;

    auto len = _write_index - _read_index;
    std::copy(_buffer.cbegin() + _read_index, _buffer.cbegin() + _write_index + 1, _buffer.begin());

    _read_index = 0;
    _write_index = len;

    std::fill(_buffer.begin() + _write_index + 1, _buffer.end(), '\0');
}

void Buffer::clear()
{
    std::fill(_buffer.begin(), _buffer.end(), '\0');
    _read_index = _write_index = 0;
}

bool Buffer::seek(int pos)
{
    if (pos < 0 || pos > _write_index)
        return false;

    _read_index = pos;
    return true;
}

