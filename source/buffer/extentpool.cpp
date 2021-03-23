#include "extentpool.h"
#include "extent.h"

// ***********************************  Free Extent Frame List  ***********************************

FreeExtentFrameList::FreeExtentFrameList()
{

}

void FreeExtentFrameList::push(ExtentFrame *frame)
{
    if (frame == nullptr)
        return;

    frame->_prev = _tail->_prev;
    frame->_next = _tail;

    _tail->_prev->_next = frame;
    _tail->_prev = frame;
}

FreeExtentFrameList::ExtentFrame* FreeExtentFrameList::pop(size_t block_size)
{
    size_t best_fit_size = 0;
    ExtentFrame* frame = nullptr;

    auto cur = _head->_next;

    while (cur != _tail)
    {
        auto extent_size = cur->_extent->size();
        if (extent_size >= block_size && extent_size < best_fit_size)
            frame = cur;
        cur = cur->_next;
    }

    if (frame != nullptr)
    {
        frame->_prev->_next = frame->_next;
        frame->_next->_prev = frame->_prev;

        --_frame_count;
    }



    return frame;
}

size_t FreeExtentFrameList::count() const
{
    return 0;
}





size_t ExtentPool::_pool_size = 500000000;

ExtentPool::ExtentPool()
{
    _start = static_cast<char*>(malloc(_pool_size * sizeof(char)));

    while (_start == nullptr)
    {
        _pool_size /= 2;
        _start = static_cast<char*>(malloc(_pool_size * sizeof(char)));
    }

    _end = static_cast<char*>(_start) + _pool_size;
}

void ExtentPool::setPoolSize(size_t s)
{
    _pool_size = s;
}

ExtentPool* ExtentPool::pool()
{
    static auto _pool = new ExtentPool;
    return _pool;
}


