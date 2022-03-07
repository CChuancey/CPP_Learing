#include <iostream>

// 懒汉模式，多线程需要加锁,有内存泄漏
// 可定义局部静态变量，返回类对象的引用
class SingleInstance {
   public:
    // 多线程加锁
    static SingleInstance* getInstance() {
        return instance ? instance : (instance = new SingleInstance);
    }

   private:
    SingleInstance() = default;
    // 静态
    static SingleInstance* instance;
};

// 若在此处直接new，不必再次加锁，但是可能浪费空间，类对象不一定用得到
// 线程较多时，使用饿汉直接初始化，以空间换时间
SingleInstance* SingleInstance::instance = nullptr;

int main() {
    SingleInstance* instance = SingleInstance::getInstance();
    if (instance) {
        std::cout << "instance create succeed!" << std::endl;
    } else {
        std::cout << "failed!" << std::endl;
    }
    return 0;
}