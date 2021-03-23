#ifndef SOURCE_EXTENTPOOL_H
#define SOURCE_EXTENTPOOL_H

#include <cstddef>

class Extent;

class FreeExtentFrameList
{
    struct ExtentFrame
    {
        Extent* _extent { nullptr };

        ExtentFrame* _prev { nullptr };
        ExtentFrame* _next { nullptr };
    };

public:

    FreeExtentFrameList();
    FreeExtentFrameList(const FreeExtentFrameList&) = delete;
    FreeExtentFrameList& operator=(const FreeExtentFrameList&) = delete;

    void push(ExtentFrame* frame);

    /*
     *  Best Fit method to allocate blocks
     * */
    ExtentFrame* pop(size_t block_size);

    size_t count() const;

private:
    ExtentFrame* _head { nullptr };
    ExtentFrame* _tail { nullptr };

    size_t _frame_count { 0 };
};


class ExtentPool
{
private:
    ExtentPool();

public:
    ExtentPool(const ExtentPool&) = delete;
    ExtentPool& operator=(const ExtentPool&) = delete;

    static void setPoolSize(size_t s);

    ExtentPool* pool();

private:
    char* _start { nullptr };
    char* _end { nullptr };

    static size_t _pool_size;
//    size_t  _frame_count { 0 };

};


#endif //SOURCE_EXTENTPOOL_H
