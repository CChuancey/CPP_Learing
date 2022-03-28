#include <complex>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

class A {
public:
    A() { std::cout << "A constructor is called!" << std::endl; }
    A(int v) : m_value(v) {}
    int getValue() const { return m_value; }
    ~A() { std::cout << "A destructor is called!" << std::endl; }

private:
    int m_value;
};

class Foo {
public:
    Foo(int i) : m_id(i) { std::cout << "call foo constructor" << std::endl; }
    ~Foo() { std::cout << "call foo destructor!" << std::endl; }
    // 重载operator new/new[]/delete/delete[]
    static void* operator new(size_t size);
    static void operator delete(void* pdead, size_t size);
    static void* operator new[](size_t size);
    static void operator delete[](void* pdead, size_t size);

private:
    int m_id = 0;
    long m_data;
    std::string m_str;
};

void* Foo::operator new(size_t size) {
    Foo* p = (Foo*)malloc(size);
    std::cout << "call my new operator expression" << std::endl;
    return p;
}

void Foo::operator delete(void* pdead, size_t size) {
    std::cout << "call my delete operator expression" << std::endl;
    free(pdead);
}

void* Foo::operator new[](size_t size) {
    Foo* p = (Foo*)malloc(size);
    std::cout << "call my new[] operator expression" << std::endl;
    return p;
}

void Foo::operator delete[](void* pdead, size_t size) {
    std::cout << "call my delete[] operator expression" << std::endl;
    free(pdead);
}

static void primitiveWay() {
    /**
     * @brief 分配/释放内存的几种方式：
     * malloc/free
     * new/delete
     * operator new()/delete
     * allocator
     */
    void* p1 = malloc(512);
    free(p1);

    /**
     * @brief new 内部调用 operator new()
     *        delete 内部调用 operator delete()
     */
    std::complex<int>* p2 = new std::complex<int>(1, 2);
    delete p2;

    A* a = new A[3];
    delete[] a;

    /**
     * @brief placement new等同于调用构造函数
     *
     */
    A* buff = new A();
    // 在buff处调用构造函数，编译器不允许显式的调用构造函数
    A* pa = new (buff) A(10);
    std::cout << pa->getValue() << std::endl;
    delete buff;

    void* p3 = ::operator new(512);
    ::operator delete(p3);

    std::allocator<int> alli;
    int* p4 = alli.allocate(512);
    alli.deallocate(p4, 512);
}

/**
 * @brief 重载new实现内存池,原始的类对象存储之间存在cookie，直接避免产生cookie
 *
 */

class Screen {
public:
    Screen(int x) : index(x) {}
    int get() { return index; }

    static void* operator new(size_t);
    static void operator delete(void*, size_t);

private:
    Screen* next;
    int index;
    static Screen* pool;
    static const int screenChunkSize;
};

Screen* Screen::pool = nullptr;
const int Screen::screenChunkSize = sizeof(Screen);

void* Screen::operator new(size_t size) {
    Screen* p = nullptr;
    if (!pool) {
        size_t chunk = screenChunkSize * size;
        // 实现的内存池
        pool = p = reinterpret_cast<Screen*>(new char[chunk]);
        for (; p != &pool[screenChunkSize - 1]; ++p)
            p->next = p + 1;
        p->next = nullptr;
    }
    p = pool;
    pool = p->next;
    return p;
}

void Screen::operator delete(void* p, size_t size) {
    (static_cast<Screen*>(p)->next) = pool;
    pool = static_cast<Screen*>(p);
}

// new/delete expression
static void newAndDeletePart() {
    /**
     * @brief operator new/new[]/delete/delete[] 可以被重载
     *
     */

    // 调用Foo类的new和delete
    Foo* f = new Foo(10);
    delete f;
    // 调用全局的new和delete
    Foo* f1 = ::new Foo(10);
    ::delete f1;

    std::cout << sizeof(Screen) << std::endl;
    size_t const N = 100;
    Screen* p[N];
    for (int i = 0; i < N; i++) {
        p[i] = new Screen(i);
    }
    for (int i = 0; i < N; i++) {
        std::cout << p[i] << std::endl;
    }
    for (int i = 0; i < N; i++)
        delete p[i];
}

/**
 * @brief 自定义allocator实现内存池管理
 *
 */
class Allocator {
public:
    void* allocate(size_t);
    void deallocate(void*, size_t);

private:
    struct obj {
        obj* next;
    };
    obj* pool = nullptr;
    const int CHUNK = 5;  // 每次分配的内存块个数为5
};

void* Allocator::allocate(size_t size) {
    obj* p = nullptr;
    if (!pool) {
        size_t chunk = CHUNK * size;
        // 实现的内存池
        pool = p = reinterpret_cast<obj*>(new char[chunk]);
        for (; p != &pool[CHUNK - 1]; ++p)
            p->next = p + 1;
        p->next = nullptr;
    }
    p = pool;
    pool = p->next;
    return p;
}

void Allocator::deallocate(void* p, size_t size) {
    static_cast<obj*>(p)->next = pool;
    pool = static_cast<obj*>(p);
}

class Good {
public:
    Good(int i) : m_index(i) {}
    static Allocator allocator;
    static void* operator new(size_t size) {
        return allocator.allocate(sizeof(Good));
    }
    static void operator delete(void* p, size_t size) {
        allocator.deallocate(p, size);
    }

private:
    int m_index;
};

// p15
int main() {
    primitiveWay();
    newAndDeletePart();
    return 0;
}