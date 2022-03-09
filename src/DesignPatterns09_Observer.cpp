#include <iostream>
#include <list>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;

class Observer {
public:
    Observer() = delete;
    Observer(string n, string t) : name(n), badThing(t) {}
    virtual void onReceivedMsg() = 0;
    string getName() { return this->name; }
    string getBadThing() { return this->badThing; }

private:
    string name;
    string badThing;
};

class Notifier {
public:
    virtual void notify() = 0;
    virtual void insertObserver(Observer*) = 0;
    virtual void deletObserver(Observer*) = 0;

protected:
    list<Observer*> lo;
};

class Student : public Observer {
public:
    Student(string n, string t) : Observer(n, t) {}
    virtual void onReceivedMsg() override {
        cout << getName() << "收到了消息" << endl;
    }

    virtual void doBadThing() {
        cout << getName() << "正在" << getBadThing() << endl;
    }
};

class Monitor : public Notifier {
public:
    virtual void notify() override {
        for (auto it : lo) {
            it->onReceivedMsg();
        }
    }
    virtual void insertObserver(Observer* obj) override { lo.push_back(obj); }
    virtual void deletObserver(Observer* obj) override { lo.remove(obj); }
    ~Monitor() {
        for (auto it : lo) {
            delete it;
        }
    }
};

int main() {
    Student* s1 = new Student("张三", "抄作业");
    Student* s2 = new Student("李四", "玩手机");
    Monitor* mon = new Monitor();

    mon->insertObserver(s1);
    mon->insertObserver(s2);

    s1->doBadThing();
    s2->doBadThing();

    mon->notify();

    delete mon;
    return 0;
}
