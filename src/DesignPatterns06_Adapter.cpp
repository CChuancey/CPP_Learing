#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// 用一个220V电源-->5V电源转换的例子

class V5 {
public:
    virtual void run() = 0;
};

class V220 {
public:
    void run() { cout << "接通了220V电源" << endl; }
};

class Adapter : public V5 {
public:
    Adapter(V220* v) : v220(v) {}

    virtual void run() { v220->run(); }

private:
    V220* v220;
};

class Phone {
public:
    Phone() = delete;
    Phone(V5* v5) : v5(v5) {}
    // 非常巧妙的将220v转移到5v上，实际调用v220的方法
    void charge() {
        cout << "充电！" << endl;
        v5->run();
    }

private:
    V5* v5;
};

int main() {
    V220* v220 = new V220();
    V5* adapter = new Adapter(v220);
    Phone* phone = new Phone(adapter);
    phone->charge();

    delete (phone);
    delete adapter;
    delete v220;
    return 0;
}