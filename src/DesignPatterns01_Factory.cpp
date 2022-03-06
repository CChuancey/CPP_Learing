#include <iostream>
// 简单工厂模式违背了“开闭原则”，可将工厂抽象，使其满足开闭原则

class Fruit {
   public:
    Fruit() = default;
    virtual void printName() const = 0;
};

class Apple : public Fruit {
   public:
    virtual void printName() const override {
        std::cout << "我是苹果" << std::endl;
    }
};

class Banana : public Fruit {
   public:
    virtual void printName() const override {
        std::cout << "我是香蕉" << std::endl;
    }
};

class Factory {
   public:
    virtual Fruit* createFruit() = 0;
};

class AppleFactory : public Factory {
   public:
    virtual Fruit* createFruit() override { return new Apple(); }
};

class BananaFactory : public Factory {
   public:
    virtual Fruit* createFruit() override { return new Banana(); }
};

int main() {
    Factory* appleFactory = new AppleFactory();
    Fruit* apple = appleFactory->createFruit();
    apple->printName();

    delete appleFactory;
    delete apple;

    return 0;
}