#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template <typename T1, typename T2, typename T3>
void callFunc(T1 fun, T2 v1, T3 v2) {
    cout << fun(v1, v2) << endl;
}

int main() {
    int x = 1;
    int y = 2;
    int z = 3;

    callFunc([](int x, int y) -> int { return x + y; }, x, y);

    // 用res记录lambda表达式,&传入引用,=传入值
    auto res = [&]() -> int { return x + y + z; };
    cout << res() << endl;

    return 0;
}