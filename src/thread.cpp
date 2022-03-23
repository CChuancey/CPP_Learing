#include <atomic>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

static double calculate(const double& v) {
    return v <= 5 ? v : sqrt((v * v + sqrt((v - 5) * (v + 2.5)) / 2.0) / v);
}

static void print() {
    for (int i = 0; i < 21470000; i++)
        calculate(rand());
}

static void test(int x) {
    cout << "hello test!\n" << endl;
}

static void atomicTest(std::atomic<int>& x) {
    x++;
}

struct BankAccount {
    BankAccount(int b) : balance(b) {}
    int balance;
    std::mutex mutex;
};

//银行账户转移,标准库提供了方法，可避免死锁的发生
static void transferMoney(BankAccount& a, BankAccount& b, int money) {
    // c++11提供的方式
    std::lock(a.mutex, b.mutex);
    std::lock_guard<std::mutex> lockA(a.mutex, std::adopt_lock);
    std::lock_guard<std::mutex> lockB(b.mutex, std::adopt_lock);
    if (&a == &b)
        return;
    a.balance -= money;
    b.balance += money;
}

// 自己实现一个class,可用它创建线程，并在结束时自动join
class ThreadGuard {
public:
    ThreadGuard(std::thread& t) : m_thread(t) {}
    ~ThreadGuard() {
        if (m_thread.joinable())
            m_thread.join();
    }

private:
    std::thread& m_thread;
};

int main() {
    clock_t start, finish;

    //给线程计时
    start = clock();
    /**
     * @brief thread构造函数的参数
     *
     * 第一个参数并不是C语言中的函数指针，而是C++11中的可调用对象
     * 可调用对象：
     * - 函数指针
     * - 重载了operator()的类对象
     * - lambda表达式
     * - bind绑定的函数
     * - std::function
     *
     *  线程对象只可以std::movemove不能复制
     */
    std::thread t(print);
    //线程的终结
    t.join();
    finish = clock();
    cout << "cost time:" << (finish - start) << endl;

    //带有参数的函数作为线程执行函数，可以使用lambda表达式,也可以直接作为参数传入
    int par = 22;
    // lambda表达式方法
    std::thread th2([&par]() { test(par); });
    th2.join();

    //直接作为参数传入，这种方式容易出错，传入的参数只能通过值拷贝的方式传入
    std::thread th3(test, par);
    th3.join();

    // atomic定义的变量，对于其++ -- + - * / 操作具有原子性，多线程安全
    std::atomic<int> x;
    std::thread testAtomic1([&x] { atomicTest(x); });
    std::thread testAtomic2([&x] { atomicTest(x); });
    std::thread testAtomic3([&x] { atomicTest(x); });
    std::thread testAtomic4([&x] { atomicTest(x); });
    std::thread testAtomic5([&x] { atomicTest(x); });

    // detach和join的区别
    /**
     * @par join:优先使用
     * 一旦调用join，主线程就会等待子线程运行结束，然后主线程在运行
     * 直到结束，传统编程就是如此，试想如果子线程访问主线程中的资源，
     * 如果主线程结束了，其中资源释放，但是子线程还在运行，要访问资源，这样的话肯定会出问题的，
     * @par detach:线程的生命周期一定要比主线程的生命周期短
     * detach，即分离的意思，一旦detach，就讲子线程交给系统托管，与进程，主线程无关了，
     * 这种情况下，就很可能主线程结束，子线程还在运行，所以detach就引发出问题，编程的难度也加大了
     *
     */

    // thread的析构函数是直接调用abort函数
    // 实际还要先判断是否可joinable if(thread.joinable()),detach后不可join
    testAtomic1.join();
    testAtomic2.join();
    testAtomic3.join();
    testAtomic4.join();
    testAtomic5.join();

    cout << x << endl;

    // 对于mutex的管理，stl中提供了lock_guard模板，解决了lock后忘记unlock的情况(析构函数的机制)
    BankAccount a(100), b(90);
    transferMoney(a, b, 10);

    // 使用自定义guard，在线程结束时自动join
    std::thread test_guard(print);
    ThreadGuard thread_guard(test_guard);

    //线程休眠函数,休眠两分钟
    std::this_thread::sleep_for(std::chrono::minutes(2));

    // 使用c++11的条件变量可以优化mutex带来的性能损失
    // #include <condition_variable>

    return 0;
}