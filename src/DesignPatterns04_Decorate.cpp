#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Phone {
public:
    virtual void show() = 0;
};

class iPhone : public Phone {
public:
    virtual void show() override { cout << "秀iPhone手机" << endl; }
};

class MiPhone : public Phone {
public:
    virtual void show() override { cout << "秀小米手机" << endl; }
};

// abstract decorate class
class Decorate : public Phone {
public:
    Decorate() = delete;
    Decorate(Phone* p) : phone(p) {}
    virtual void show() = 0;

protected:
    Phone* phone;
};

class MoDecorate : public Decorate {
public:
    MoDecorate() = delete;
    MoDecorate(Phone* p) : Decorate(p) {}
    virtual void show() override {
        phone->show();
        cout << "手机已经贴膜!" << endl;
    }
};

int main() {
    Phone* iphone = new iPhone();
    Decorate* moDecorate = new MoDecorate(iphone);
    moDecorate->show();

    delete moDecorate;
    delete iphone;
    return 0;
}