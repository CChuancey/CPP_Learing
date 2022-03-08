#include <iostream>
#include <memory>  //智能指针的头文件
#include <vector>
// 引用数为0时释放内存
// 对于需要保留内存空间的对象，可以将所有的智能指针存放到一个容器中

// 定义shared_ptr时，第二个参数可以指定自定义释放函数

void process(std::shared_ptr<int> p) { return; }

int main() {
    std::shared_ptr<int> ptr = std::make_shared<int>(10);
    std::cout << *ptr << std::endl;

    // shared_ptr和new结合使用
    // 智能指针类型和内置指针类型不兼容
    // std::shared_ptr<int> p1 = new int(10); //错位写法
    // 将智能指针初始化并绑定到堆区的内存上
    std::shared_ptr<int> p1(new int(10));

    std::shared_ptr<int> p(new int(1024));
    process(std::shared_ptr<int>(p));
    process(p);
    std::cout << *p << std::endl;

    // process(std::shared_ptr<int>(p.get())); //执行完即释放p.get()的内存
    // std::cout << *p << std::endl;

    auto sp = std::make_shared<int>();
    auto p3 = sp.get();
    //    delete p3;

    /** unique_ptr**********************/
    std::unique_ptr<int> up(new int);
    // std::unique_ptr<int> uq = up;

    int* pa = new int[1024];
    delete[] pa;
    return 0;
}