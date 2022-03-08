#include <iostream>
#include <string>

#if 0
// 不考虑设计模式的写法，增加水果种类导致构造函数记为复杂
class Fruit {
   public:
    Fruit() = default;
    Fruit(std::string label) {
        if (label == "apple") {
            name = std::string("苹果");
        } else if (label == "banana") {
            name = std::string("香蕉");
        }
    }
    virtual void printName() const { std::cout << name << std::endl; }

   private:
    std::string name;
};
#endif

// 使用简单工厂模式，设计一个水果工厂类，并将各种水果作为子类分离出来
class Fruit {
public:
    Fruit() = default;
    virtual void printName() const = 0;
};

class Apple : public Fruit {
public:
    virtual void printName() const { std::cout << "我是苹果" << std::endl; }
};

class Banana : public Fruit {
public:
    virtual void printName() const { std::cout << "我是香蕉" << std::endl; }
};

// 但是它破坏了“开闭原则”，当新增水果种类时，需要修改FruitFactory的代码
class FruitFactory {
public:
    FruitFactory() = default;
    Fruit* createFruit(std::string name) {
        Fruit* ret = nullptr;
        if (name == "apple") {
            ret = new Apple;
        } else if (name == "banana") {
            ret = new Banana;
        }
        return ret;
    }
};

int main() {
#if 0
    Fruit* apple = new Fruit("apple");
    apple->printName();
#endif
    FruitFactory* factory = new FruitFactory();
    Fruit* apple = factory->createFruit("apple");
    Fruit* banana = factory->createFruit("banana");
    apple->printName();
    banana->printName();

    delete apple;
    delete banana;
    delete factory;
    return 0;
}