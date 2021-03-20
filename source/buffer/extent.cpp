#include "extent.h"
#include "extentpool.h"


using std::atomic_bool;
using std::string;


void Extent::withdraw(Pool& pool, char* data, size_t n)
{
    if (_data != nullptr || data == nullptr)
        return;

    _data = data;
    _capacity = n;
    _pool = pool;
}


void Extent::deposit()
{

}


void Extent::occupy()
{
    _in_use = true;
}


void Extent::free()
{
    _in_use = false;
}


string Extent::read()
{
    if (_reader == 0 || _reader == _writer)
        return "";

    string output(_data + _reader, _data + _writer);
    _reader = _writer;
    return output;
}


bool Extent::write(const string &content)
{
    auto len = content.size();
    if (len > _capacity - _writer)
        return false;

    std::copy(content.cbegin(), content.cend(), _data + _writer);
    _writer = len;
    return true;
}


bool Extent::remark(unsigned int pos)
{
    if (pos >= _reader)
        return false;

    _reader = pos;

    return true;
}


void Extent::refresh()
{
    if (_reader == 0)
        return;

    auto len = _writer - _reader;
    std::copy(_data + _reader, _data + _writer + 1, _data);

    _reader = 0;
    _writer = len;

    std::fill(_data + _writer + 1, _data + _capacity, '\0');
}


string Extent::data() const
{
    return string(_data);
}


size_t Extent::size() const
{
    return _size;
}


std::string Extent::read(unsigned int amount)
{
    if (amount >= _writer - _reader)
        return read();

    string output(amount, ' ');
    auto beg = output.begin();

    while (amount > 0)
    {
        *beg = _data[_reader];
        ++_reader;
        ++beg;
    }

    return output;
}


size_t Extent::available_write() const
{
    return _capacity - _writer;
}


size_t Extent::available_read() const
{
    return _writer - _reader;
}

size_t Extent::expand()
{
    return 0;
}


