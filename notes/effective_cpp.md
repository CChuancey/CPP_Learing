# 01 C++是一个语言联邦

> - C的部分
> - OO 面向对象部分
> - C++的模板部分
> - STL部分

# 02 不使用#define

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

# 03 尽量使用const

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

 # 04 对象使用前必须初始化

# 05 默认的Copy Constructor/assignment 

- 普通的成员变量，copy每一个bit
- 对于reference/const类型，编译器拒绝赋值操作（编译不通过）

# 06 不想让编译器自动生成的函数，就应该明确拒绝

- 将其权限声明为private
- `=delete`

# 07 使用多态的基类声明virtual析构函数

- 任何class只要带有virtual函数都要有virtual析构函数
- 将所有的class的析构函数都声明为virtual也是错误的，会导致额外的开销
- 如果不是用作多态使用，就不应该声明为virtual析构函数

# 08 析构函数不要抛出异常

- 两个异常同时存在的情况下，程序可能出现不确定的行为
- 析构函数不要抛出异常；
- 析构函数应该捕捉任何异常，然后结束程序/不再抛出
- 如果需要对某个操作函数运行期间抛出的异常做出反应，class应单独提供一个函数，而不是放在析构函数中

# 09 不在构造和析构函数中调用virtual函数

- 构造函数：如果基类的构造函数中调用了虚函数；子类在初始化时会调用父类的构造函数，此时调用的虚函数是属于父类的
- 析构函数：子类析构时会调用父类的析构函数，同样也会调用到父类的虚函数

# 10 operator= 返回一个reference to *this

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

# 11 在operator= 中处理自我赋值

- 在operator=中考虑对象自我复制的情况；
- 确定任何一个函数如果操作多个对象，而其中多个对象是同一对象时，其行为仍然正确。

# 12 深拷贝

- 确保复制所有local成员变量
- 调用所有base class内的合适的copying函数

> copy assignment和copy函数之间不应该互相调用。
>
> 如果要复用其中的代码，应该单独封装成一个private的函数















