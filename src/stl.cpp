#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::array;
using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::forward_list;
using std::list;
using std::map;
using std::multiset;
using std::set;
using std::string;
using std::vector;

/**
 * @brief
 *  容器类型（Contanier）
 *  1.序列式容器：array/vector/list/deque/list/forward_list
 *  2.关联类容器：set/map/multiset/multimap
 *  3.无顺序容器：unordered_set/unordored_map/unordered_multiset/unordered_multimap
 */

// 容器的通用操作
template <typename T>
static void containerCommonInterface(T& a, T& b) {
    T c;
    T d(a);
    T e = a;
    T f(std::move(a));  // 执行后，a虽然是个完整的类，但数据都被转移到f中了
    auto itb = b.begin();  // auto即可
    auto ite = b.end();
    T g(b.begin(), b.end());
    b.size();  // forwad_list 容器不提供size函数接口
    b.empty();
    b.max_size();

    // 对于array，swap时间复杂读为O(N)，其余为O(1)
    e.swap(g);
    std::swap(e, g);

    e.cbegin();  // const_iterator

    e.crbegin();  //反向const迭代器
    e.crend();

    e.clear();
}

static void arraryPart() {
    // array是对原生数组进行的封装
    array<int, 100> ai;
    array<int, 50> bi{};  //初始化

    array<int, 10> ci{1, 2, 3, 4, 5};
    cout << ci.front() << "\t" << ci.back() << endl;

    ci.fill(6);
    cout << ci[6] << endl;

    // at 会抛出异常
    // ci.at(10);
    cout << "array partition end!" << endl;
}

static void vectorPart() {
    vector<int> a;
    vector<int> b{2, 3, 4, 5, 67, 8, 9};
    /**
     * size:当前容器中的元素个数
     * capacity：当前容器不会扩容的最大容量
     * max_size：最大支持的容量
     */
    cout << b.size() << "\t" << b.capacity() << "\t" << b.max_size() << endl;

    vector<int> c;  // 空间为0
    c.reserve(50);  //预先申请50个元素空间
    cout << c.size() << "\t" << c.capacity() << endl;

    c.clear();     //清空
    c.resize(10);  //重设capacity

    c.shrink_to_fit();
    cout << c.capacity() << endl;
    // c.at(1); //检查是否越界抛出异常

    // 对于front和back操作，一定要先保证容器非空
    if (!c.empty()) {
        c.front();
        c.back();
        c.pop_back();
        auto itAfter = c.erase(c.begin());  //返回删除元素的下一个元素的迭代器
        c.erase(c.begin(), c.end());
    }

    // insert插入
    // 迭代器位置和值
    auto iter = c.insert(c.end(), 123);
    // 迭代器位置、数量和值
    iter = c.insert(c.end(), 10, 456);
    cout << *c.begin() << "\t" << *c.rbegin() << endl;

    // emplace：使用构造而非拷贝！！！！！！！！！！             c++11新特性

    // 一定不能使用vector<bool>!!

    cout << "vector partition end!" << endl;
}

static void dequePart() {
    // 随机访问元素、末端和头部添加删除元素效率高。中间添加删除元素效率低
    // 元素访问和迭代速度比vector慢

    // deque无法预分配内存
    deque<int> di{1, 2, 34, 57};
    di.push_front(99);
    di.push_back(123);
    cout << di.front() << "\t" << di.back() << endl;

    cout << "deque partition end" << endl;
}

static void listPart() {
    // list的遍历比vector和deque慢
    // list 支持的算法
    list<int> b{1, 1, 2, 2, 2, 3, 4, 5, 5, 6};
    b.remove(2);                               // 删除所有2
    b.remove_if([](int x) { return x > 5; });  // 删除所有大于5的元素

    for (const auto& it : b) {
        cout << it << "\t";
    }
    cout << endl;

    //颠倒元素顺序
    b.reverse();
    b.unique();  //在有序list中剔除重复元素
    list<int> c;
    c.splice(c.begin(), b);  //将b整个插入到c的开头处

    // 不存在这种写法！！！，list内部实现了sort函数
    // std::sort(c.begin(), c.end());
    c.sort();

    cout << "list partition end" << endl;
}

static void forwardListPart() {
    forward_list<int> fi{1, 2, 4, 5, 6, 7, 8};
    // 仅支持获取头部元素的操作
    cout << fi.front() << endl;

    // 插入是insert forward，删除是erase after

    cout << "forward list partition end" << endl;
}

static void setPart() {
    set<int> si{1, 2, 3, 4, 5, 6, 7, 9};
    multiset<int> msi{4, 1, 2, 2, 4, 5, 0, 8, 1, 5, 8};

    //对于si的查找
    cout << si.count(2) << endl;
    // 对于multiset的查找判定是否存在
    cout << (msi.find(2) != msi.end()) << endl;

    // set中的lower_bound和upper_bound
    //返回大于等于的位置
    auto iter1 = std::lower_bound(si.begin(), si.end(), 5);
    //返回大于的位置
    auto iter2 = std::upper_bound(si.begin(), si.end(), 5);
    cout << "iter1: " << *iter1 << "  iter2: " << *iter2 << endl;

    // insert操作返回值为pair:<iterator,bool>

    // set内置的find采用的比较函数是定义时指定的比较器，时间复杂度为O(logn)
    // std::find采用的比较函数是成员的operator==,时间复杂度为O(N)

    cout << "set/multiset partition end" << endl;
}

static void mapPart() {
    map<string, int> msi{{"AA", 1}, {"BB", 2}, {"CC", 3}};
    map<string, int> msb;

    // 插入元素的几种方式
    auto state = msi.insert(std::make_pair("DD", 4));
    msb.insert(msi.begin(), msi.end());
    //两种右值的形式插入
    msi.emplace(std::make_pair("pair", 12));
    msi.emplace("emplace string", 21);

    msi["test"];  //如果test不在map中会生成一个pair<test,0>

    cout << "set/multiset partition end" << endl;
}

static void unorderedPart() {
    // unordered 容器采用hash实现，当数据量达到百万级以上时，效率比ordered低
    // unordered无法有序遍历，自定义类型需要实现hash模板特化
    cout << "unordered partition end" << endl;
}

int main() {
    vector<int> a{1, 2, 3, 4};
    vector<int> b{5, 6, 7, 8, 9};
    containerCommonInterface(a, b);  // 容器的通用接口

    arraryPart();
    vectorPart();
    dequePart();
    listPart();
    setPart();
    mapPart();

    return 0;
}