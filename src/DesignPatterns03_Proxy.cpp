#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Item {
   public:
    Item() = default;
    Item(string n, string k, string t) : name(n), kind(k), type(t) {}
    string getName() { return name; }
    string getType() { return type; }

   private:
    string name;
    string kind;
    string type;
};

class Shopping {
   public:
    virtual void buy(Item*) = 0;
};

class USAbuy : public Shopping {
   public:
    virtual void buy(Item* item) {
        cout << "去美国买" << item->getName() << endl;
    }
};

class OverseaBuy {
   public:
    OverseaBuy() = default;
    OverseaBuy(Shopping* s) : shopping(s) {}
    void buy(Item* item) {
        // buy套buy，同时可以加业务逻辑代码
        if (item->getType() == "true") {
            shopping->buy(item);
        }
    }

   private:
    Shopping* shopping;
};

int main() {
    Item* apple = new Item("nike", "shoes", "true");
    Shopping* usaShopping = new USAbuy();
    OverseaBuy* overseaBuy = new OverseaBuy(usaShopping);
    overseaBuy->buy(apple);
    delete usaShopping;
    delete overseaBuy;
    delete apple;
    return 0;
}