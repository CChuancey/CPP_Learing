#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// 外观模式，场景如下：
// 考虑智能家居的场景：智能家具包括智能冰箱、智能洗衣机、智能电视和智能灯；
// 可以封装好两种应用场景：1、家庭影院模式：电视开启、灯关闭；2、洗衣模式：洗衣机工作
class AIAppliance {
public:
    virtual void run() = 0;
    virtual void stop() = 0;
};

class Fridge : public AIAppliance {
public:
    void run() override { cout << "智能冰箱工作" << endl; }
    void stop() override { cout << "智能冰箱停止工作" << endl; }
};

class Washer : public AIAppliance {
public:
    void run() override { cout << "智能洗衣机工作" << endl; }
    void stop() override { cout << "智能洗衣机停止工作" << endl; }
};
class TV : public AIAppliance {
public:
    void run() override { cout << "智能电视工作" << endl; }
    void stop() override { cout << "智能电视停止工作" << endl; }
};

class Light : public AIAppliance {
public:
    void run() override { cout << "智能灯工作" << endl; }
    void stop() override { cout << "智能灯停止工作" << endl; }
};

// 提供给用户的两种外观
class WorkingModel {
public:
    void homeTheater() {
        tv.run();
        light.stop();
    }
    void washMode() { washer.run(); }
    Fridge frige;
    Washer washer;
    TV tv;
    Light light;
};

int main() {
    WorkingModel* woker = new WorkingModel();
    woker->homeTheater();
    delete woker;
    return 0;
}
