# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

include_directories("../channel")
include_directories("../dispatcher")
include_directories(../common)

# 生成链接库
add_library (EventLoop ${DIR_LIB_SRCS} eventloop.cpp)