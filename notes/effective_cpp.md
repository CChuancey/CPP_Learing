# Part1 让自己习惯C++

## 01 C++是一个语言联邦

> - C的部分
> - OO 面向对象部分
> - C++的模板部分
> - STL部分

## 02 不使用#define

> #define 无法实现private级别的权限保护
>
> class中的static const常量值,在类声明(.h)中声明并初始化，在cpp文件中定义一次
>
> ```c++
> class MyClass{
> public:
>     MyClass(int v):m_value(v){}
>     void print(){
>         std::cout << m_value << " x: "<< &x << std::endl;
>     }
> private:
>     // 声明并初始化,如果不涉及对x的取地址操作，不需要再在类外面定义一次
>     static const int x=110;
>     int m_value;
> };
> 
> // 定义
> const int MyClass::x;
> 
> int main(){
>     MyClass mc(100);
>     mc.print();
>     return 0;
> }
> 
> ```
>
> \#define 实现的函数要用inline代替

## 03 尽量使用const

- 两个成员函数如果**只是常量性不同**，可以被重载

- const和non-const的成员函数会有大量代码重复，可以用non-const版本的调用const版本的减少代码冗余

- 为变量添加const属性可以使用`static_cast<const T>`，但是要消除变量的const属性，只能使用`const_cast<T&*>`

  ```c++
  int a = 10;
  const int b = static_cast<const int>(a);
  int& c = const_cast<int&>(b);
  c = 104984894
  // a=10,b=104984894,c=104984894
  ```

- 声明为const可以让编译器检查错误用法

 ## 04 对象使用前必须初始化

---

# Part2 构造/析构/赋值运算

## 05 默认的Copy Constructor/assignment 

- 普通的成员变量，copy每一个bit
- 对于reference/const类型，编译器拒绝赋值操作（编译不通过）

## 06 不想让编译器自动生成的函数，就应该明确拒绝

- 将其权限声明为private
- `=delete`

## 07 使用多态的基类声明virtual析构函数

- 任何class只要带有virtual函数都要有virtual析构函数
- 将所有的class的析构函数都声明为virtual也是错误的，会导致额外的开销
- 如果不是用作多态使用，就不应该声明为virtual析构函数

## 08 析构函数不要抛出异常

- 两个异常同时存在的情况下，程序可能出现不确定的行为
- 析构函数不要抛出异常；
- 析构函数应该捕捉任何异常，然后结束程序/不再抛出
- 如果需要对某个操作函数运行期间抛出的异常做出反应，class应单独提供一个函数，而不是放在析构函数中

## 09 不在构造和析构函数中调用virtual函数

- 构造函数：如果基类的构造函数中调用了虚函数；子类在初始化时会调用父类的构造函数，此时调用的虚函数是属于父类的
- 析构函数：子类析构时会调用父类的析构函数，同样也会调用到父类的虚函数

## 10 operator= 返回一个reference to *this

```c++
class Widget{
public:
    // ....
    Widget& operator=(const Widget& rhs){
        //**
        return *this;
    } 
};
```

## 11 在operator= 中处理自我赋值

- 在operator=中考虑对象自我复制的情况；
- 确定任何一个函数如果操作多个对象，而其中多个对象是同一对象时，其行为仍然正确。

## 12 深拷贝

- 确保复制所有local成员变量
- 调用所有base class内的合适的copying函数

> copy assignment和copy函数之间不应该互相调用。
>
> 如果要复用其中的代码，应该单独封装成一个private的函数



---

# Part3 资源管理

## 13 用对象来管理资源

- 为防止资源泄漏，使用RAII对象，在构造函数中获得资源并在析构函数中释放资源
- 尽可能使用智能指针管理资源

## 14 资源管理类中注意copy的行为

- 复制RAII对象必须一并复制它所管理的资源，资源的copy的行为决定RAII对象的copy行为

## 15 在资源管理类中提供对原始资源的访问

- C/C++混合编程，提供给C语言的接口往往是裸的指针，所以每一个RAII class应该提供一个提供对原始资源访问的方法
- 可以显示的提供（shared_ptr中的get函数）
- 可以隐士的提供（考虑重载operator()）

## 16 成对使用new/delete时要采取相同的形式

- new-delete new[]-delete[]

## 17 将new对象放入智能指针后再进行传递参数

```c++
class Res{
public:
    Res(std::shared_ptr<MyClass> smy):c(smy){

    }
private:
    std::shared_ptr<MyClass> c;

};
Res res(std::shared_ptr<MyClass>(new MyClass()));
```

---

# Part4 设计与声明

## 18 设计的接口要容易被使用，不易被误用

- 保持接口的一致性以及与内置类型行为兼容
- 建立新类型、限制类型上的操作、束缚对象值等方法可以尽可能阻止误用

 ## 19 设计class犹如设计type一样艰难

- 对象的创建和销毁
- 对象的初始化和对象的复制
- copy函数用来定义一个type的pass-by-value如何实现
- 什么是新type的合法值
- 需要继承体系吗
- 新type需要什么样的类型转换
- 需要对其设计什么样的operator
- 需要template化吗

## 20 用pass-by-reference-to-const替换pass-by-value

- 对于内置类型，一律采用pass-by-value的方式

- 对于自定义类型/STL等，最好采用pass-by-reference-to-const

  > reference内部采用指针实现，涉及到多态下的参数传递时，还可以避免引pass-by-value导致的对象切割问题，只能传递基类部分

## 21 函数返回对象时，不要返回reference

- 不要用pointer或reference指向一个local stack对象

  ```c++
  //（C++11可 std::move配合右值引用） 以下代码有待验证，调用了4次析构
  class MyClass
  {
  public:
      MyClass(int v):m_value(v) {}
      void print()
      {
          std::cout << m_value << " x: "<< x << std::endl;
      }
      int operator()() const
      {
          return m_value;
      }
      ~MyClass(){
          std::cout <<m_value<< " ~ fun" << std::endl;
      }
  
  private:
      static enum
      {
          x=10
      } m;
  //    static const int x=110;
      const int m_value;
  };
  
  // 二元opertor*定义在class外部
  const MyClass&& operator*(const MyClass& lhs,const MyClass& rhs){
      return std::move(MyClass(lhs()*rhs()));
  }
  
  int main(){
      MyClass a(3),b(2);
      MyClass c = a*b;
      c.print();
      return 0;
  }
  ```

- 不要用reference指向一个返回的heap-allocated对象,如a=b*c，b,c是函数返回的heap-allocated对象，不去释放就容易内存泄漏

- 不要用reference/pointer指向一个local static对象，而有可能同时需要多个这样的对象，造成多线程不安全

## 22 将成员变量声明为private

- 成员变量应该隐藏起来，每个成员变量都需要一个getter和setter的情况罕见
- 将成员变量声明为private提供了封装，使得对其他对象操作成员变量时提供了约束
- protected和public都不具有封装性
  - 对于public：如果成员变量发生了改变，与之相关的类都要修改
  - 对于protected：如果成员变量发生了改变，derived类都要做出改变

## 23 尽可能使用non-member-non-friend函数替换member函数

- 能够访问private成员变量的函数只有member函数和friend函数，故而non-member且non-friend函数能够提供较大的封装性
- 将non-member-non-friend函数和class放入一个namespace，namespace可以跨文件

## 24 如果所有参数都需要类型转换，采用non-member函数

```c++
class Rational{
public:
    Rational(int numerator=0,int denominator=1):num(numerator),demo(denominator){}
    int getNum() const {return num;}
    int getDemo() const {return demo;}
    void print() const {
        std::cout << num << "/" << demo << std::endl;
    }
private:
    int num;
    int demo;
};

// 定义为non-member函数
const Rational operator*(const Rational& lhs,const Rational& rhs){
    return Rational(lhs.getNum()*rhs.getNum(),lhs.getDemo()*rhs.getDemo());
}

Rational ra(1,2),rb(3,4);
Rational d = ra*2; // Rational类的构造函数为声明为explicit，2隐式转换为Rational类
d.print();
Rational e = 3*d; //如果定义为member函数，此句就会出错 
```

## 25 写出一个不抛出异常的swap函数

- 当std::swap提供的swap函数效率不高时，提供一个swap成员函数，并确定它不会抛出异常
- 如果提供了一个member swap，也应该提供一个non-member swap来调用它；并且再提供特化版本的std::swap
- 可以为用户定义类型进行std templates全特化，但是不能再标准空间内添加新的templates

```c++
namespace myspace{
class Widgets{
public:
    void swap(Widgets& other)
    {
        using std::swap;
        swap(v,other.v);
    }


private:
    int v;//v是swap过程中类中唯一需要swap的

};

void swap(Widgets& a,Widgets& b){
    a.swap(b);
}

}

namespace std{
    using myspace::Widgets;
    template<>
    void swap<Widgets>(Widgets& a,Widgets& b)    {
        a.swap(b);
    }
}
```















