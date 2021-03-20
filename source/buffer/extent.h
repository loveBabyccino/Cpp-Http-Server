#ifndef SOURCE_EXTENT_H
#define SOURCE_EXTENT_H

#include <memory>
#include <atomic>

#include <string>


class ExtentPool;


class Extent
{
    using Pool = std::weak_ptr<ExtentPool>;
    using InUseFlag = std::atomic_bool;

public:
    void withdraw(Pool& pool, char* data, size_t n);

    void deposit();

    void occupy();

    void free();

    bool remark(unsigned  int pos);

    void refresh();

    std::string read();

    std::string read(unsigned int amount);

    bool write(const std::string& content);

    size_t expand();

    size_t available_write() const;

    size_t available_read() const;

    std::string data() const;

    size_t size() const ;


private:
    unsigned int _reader {0};
    unsigned int _writer {0};

    char* _data { nullptr };
    size_t _size { 0 };
    size_t _capacity { 0 };

    InUseFlag _in_use { false };

    Pool _pool;

};


#endif //SOURCE_EXTENT_H
