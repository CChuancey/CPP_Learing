#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    static_assert(sizeof(int)==4,"this function is only for 32bit system!");
    return 0;
}