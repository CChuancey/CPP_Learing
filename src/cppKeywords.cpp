#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

vector<int> makeVector(const size_t size) {
    vector<int> vi(size);
    for (int i = 0; i < size; i++) {
        vi[i] = i + 5;
    }
    return vi;
}

int makeInteger(const int v) {
    return v;
}

class A {
public:
    ~A() noexcept(false) { throw "123"; }
};

void testA() {
    try {
        A a;
        // A b;
    } catch (...) {
        cout << "find a error!" << endl;
    }
}

int main(int argc, char* argv[]) {
    static_assert(sizeof(int) == 4, "this function is only for 32bit system!");

    vector<int>&& rvalue = makeVector(10);
    for (int i = 0; i < 10; i++) {
        rvalue[i] = i + 10;
    }

    // vector<int>& lvalue = std::move(rvalue);

    for (int i = 0; i < 10; i++) {
        cout << rvalue[i] << endl;
    }
    testA();
    return 0;
}