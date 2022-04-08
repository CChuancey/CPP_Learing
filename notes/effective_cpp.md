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























