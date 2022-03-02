#include <list>
#include <string>
#include <vector>
#include "class01.h"

int main() {
    std::list<int> l1;
    std::list<int>::iterator iter1 = l1.begin(), iter2 = l1.end();
    while (iter1 != iter2) {
        iter1++;
    }
    std::list<int> l2(10, 555);
    for (auto i : l2) {
        std::cout << i << std::flush;
    }
    std::cout << std::endl;
    std::list<int> li(10, 1);
    li.push_back(2);

    std::list<double> ld(li.begin(), li.end());
    std::vector<double> vd(li.begin(), li.end());
    for (auto d : vd) {
        std::cout << d << std::endl;
    }
    return 0;
}