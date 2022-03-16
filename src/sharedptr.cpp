#include <iostream>
#include <memory>

using std::cin;
using std::cout;
using std::endl;

class A {
public:
    A() = default;
};

using ObjectPtr = std::shared_ptr<A>;

void printCountNum(const ObjectPtr& ptr) {
    cout << ptr.use_count() << endl;
}

void myDelete(A* a) {
    if (a) {
        cout << "调用自定义析构" << endl;
        delete a;
    }
}

//***********循环引用**********************/
class Child;
using ChildPtr = std::shared_ptr<Child>;
using ChildWeakPtr = std::weak_ptr<Child>;

class Parent {
public:
    Parent() = default;
    ChildWeakPtr ptr;
    ~Parent() { cout << "Parent的析构被调用！" << endl; }
    void checkRelation();
};
using ParentPtr = std::shared_ptr<Parent>;
using ParentWeakPtr = std::shared_ptr<Parent>;

class Child {
public:
    Child() = default;
    ParentPtr ptr;
    ~Child() { cout << "Child的析构被调用！" << endl; }
    void checkRelation();
};

class OBJ {
public:
    OBJ() = default;
};
using OBJPtr = std::unique_ptr<OBJ>;

void handleChildAndParentRef(const Child& child, const Parent& parent) {
    if (child.ptr.get() == &parent && parent.ptr.lock() &&
        parent.ptr.lock().get() == &child) {
        cout << "right relation" << endl;
    } else {
        cout << "oop" << endl;
    }
}

void handleChildAndParent(const ChildPtr& child, const ParentPtr& parent) {
    if (child->ptr == parent && parent->ptr.lock() &&
        parent->ptr.lock() == child) {
        cout << "right relation" << endl;
    } else {
        cout << "oop" << endl;
    }
}

void Parent::checkRelation() {
    ChildPtr c = ptr.lock();
    if (c) {
        // 两个智能指针管理同一个区域，两次析构；可通过CRTP机制解决
        // c++ 奇特的递归模板模式(CRTP)
        ParentPtr p(this);
        handleChildAndParent(c, p);
    }
}

void Child::checkRelation() {}

void testParentAndChild() {
    ParentPtr p(new Parent);
    ChildPtr c(new Child);
    p->ptr = c;
    c->ptr = p;
    p->checkRelation();
}

int main() {
    ObjectPtr null;  // 未传入地址
    cout << null.use_count() << endl;

    ObjectPtr ptr(new A);
    cout << ptr.use_count() << endl;

    ObjectPtr ptr2(ptr);
    cout << ptr.use_count() << endl;

    // 在使用途中释放指针
    ptr2.reset();
    cout << ptr.use_count() << endl;

    // 交换智能指针管理的内容
    ptr.swap(null);
    cout << ptr.use_count() << endl;

    std::swap(ptr, null);
    cout << ptr.use_count() << endl;

    // 检查指针管理的内容是否有只有一个指针在管理
    if (ptr.unique()) {  // 比use_count 效率高
        cout << "管理的指针唯一！" << endl;
    }
    printCountNum(ptr);

    // 在构造智能指针的时候指定删除的函数
    ObjectPtr obj(new A, myDelete);
    // 错误写法
    // ObjectPtr obj2 = std::make_shared<A>(new A,myDelete);

    // 循环引用的情况
    // ParentPtr par(new Parent);
    // ChildPtr child(new Child);
    // par->ptr = child;
    // child->ptr = par;

    // new 和shared_ptr混用导致两次delete
    // testParentAndChild();

    /*************** unique_ptr ***********************/
    OBJPtr objPtr(new OBJ);
    // objPtr放弃管理内存，reset是释放内存
    // OBJ* o = objPtr.release();
    // delete o;

    // 将unique_ptr转换为shared_ptr
    std::shared_ptr<OBJ> sobjPtr(std::move(objPtr));
    if (objPtr == nullptr) {
        cout << "unique_ptr转换成了shared_ptr，并成为空指针!" << endl;
    }

    return 0;
}