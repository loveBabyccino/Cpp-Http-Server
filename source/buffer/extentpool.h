#ifndef SOURCE_EXTENTPOOL_H
#define SOURCE_EXTENTPOOL_H

#include <memory>

class ExtentPool
{
public:
    ExtentPool(size_t size = 500000000);

private:
    bool accessible { true };

//    std::shared_ptr<void*> _start;

    void* _start { nullptr };
    void* _end { nullptr };

//    Extent* _free_frame { nullptr };

    size_t _pool_size { 0 };
    size_t  _frame_count { 0 };
};


#endif //SOURCE_EXTENTPOOL_H
