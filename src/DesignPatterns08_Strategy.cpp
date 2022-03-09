#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Strategy {
public:
    virtual double sale_strategy(double price) = 0;
};

class PromotionStrategy : public Strategy {
public:
    virtual double sale_strategy(double price) override { return price * 0.8; }
};

class Item {
public:
    Item(string name, double price) : name(name), price(price) {}

    void setSaleStrategy(Strategy* s) {
        strategy = s;
        price = strategy->sale_strategy(price);
    }

    double getPrice() { return price; }
    ~Item() {
        if (strategy) {
            delete strategy;
        }
    }

private:
    string name;
    double price;
    Strategy* strategy;
};

int main() {
    Item* it = new Item("水果", 100);
    cout << "当前价格:" << it->getPrice() << endl;
    Strategy* s = new PromotionStrategy();
    it->setSaleStrategy(s);
    cout << "当前价格:" << it->getPrice() << endl;
    return 0;
}