# CPP_Learing

> 暂定学习路线：
>
> - Essential C++
> - C++ Primer 第五版
> - Effective C++

## Essential C++

---

8.11

成就：完成Essential C++的第一章

收获与心得：

- 关于对象的初始化，C语言风格是`=`直接赋值，C++风格则是构造函数法（列表）
- 内置类型可以直接使用 `std::cin`和`std::cout`输入输出，自定义类需要重载`<<`与`>>`
- C++的文件IO用到头文件`fstream`



---

8.12

成就：完成Essential C++的第二章

收获与心得：

- 提领指针之前，一定要盘断是否为空指针
- C++没有提供任何可以在`new`数组的同时对数组进行初始化
- `new`创建的用`delete`销毁，`new[]`创建的用`delete[]`销毁
- 函数参数使用**引用**时，引用的值不能是空(nullptr或0)
- 函数使用默认参数时，参数默认值只能说明一次，且要在函数声明处指定
- 重载函数不能以返回值的类型区分，因为调用时无法选择
- 重载函数中对变量的处理只有类型不同时，考虑模板函数
- **inline函数的定义必须在头文件完成**

---

8.13、8.14、8.15

成就：完成Essential C++的第三章

收获与心得：

- array和vector都可以template实现基于指针的顺序查找
- 顺序容器可以使用`iterator`依次访问每个元素（对于`const`修饰的容器，访问时要用`const_iterator`）
-  了解到function object机制，用来代替运算符
- 定义顺序容器对象的五种方式
- vector等容器可以在函数中定义且可以返回其地址。不会销毁！！
- 了解到泛型编程的机制与iterator的使用

---

8.20

成就：完成Essential C++的第四章

收获与心得：

- 使用`=`符号给class object赋值时，会自动转换为对应的构造函数

- 使用`=`符号实现class object之间的拷贝时，如果不重载`=`,默认情况下两个class object的栈区和堆区的内容都相同

- A类要访问B类的private内容时，需要声明`friend`类

- `<<`和`>>`运算符不是member function

- **函数指针的typedef**：`typedef void (Triangular::*PtrFunc)(int);` 此后`PtrFunc`代表void f(int)类型的函数指针，可以使用`PtrFunc ptr`的方式定义函数指针

- 指向class member function的指针用法

  ```c++
  class Triangular{
  public:
      void func(int x){
          std::cout << "Your func is " << x << std::endl;
      }
  private:
  
  };
  typedef void (Triangular::*FuncPtrType)(int);
  
  int main()
  {
  
      FuncPtrType ptr = Triangular::func;
      Triangular tr;
      (tr.*ptr)(1);
      return 0;
  }
  
  ```

  















