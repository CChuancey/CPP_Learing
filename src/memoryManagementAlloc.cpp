#include <ext/pool_allocator.h>  //__pool_alloc要用的头文件，要使用std::allocator之外的allocator就需要
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main() {
    // 使用gnu的pool_alloc内存池分配器
    std::vector<std::string, __gnu_cxx::__pool_alloc<std::string>> vs;
    return 0;
}