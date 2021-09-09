# Chapter01：编程基础

vector的初始化：`vector<int> vi(array,array+length);`,需要提供首末地址

## 文件读写

- 头文件：`#include<fstream>`

- 写文件

  ```c++
  ofstream outfile("test.txt"); //文件不存在会创建；文件存在会被截断
  ofstream outfile("test.txt",ios_base::app);//以追加方式写
  ```

- 读文件

  ```c++
  ifstream myfile("text.txt");
  if(!myfile){
      return -1;//未打开
  }else{
      string name;
      int nt,nc;
      //返回值为从myfile读到的class object，读到文件末尾时，对class object求值结果为false
      while(myfile >> name >> nt >> nc){
          if(name=="chuancey"){
              cout << "welcome chuancey"
                  << "Your current socore is " << nc
                  << "out of " << nt << "\nGood Luck!\n";
          }
      }
  }
  ```

- 同时读写

  ```c++
  fstream iofile("test.txt",ios_base::app||ios_base::in);//需要以追加方式打开，否则会截断文件
  if(!iofile){//打不开
      return -1;
  }else{
      //打开后将文件指针重定位至起始处
      iofile.seekg(0);
  }
  ```

  

# Chapter 03 泛型编程风格

## 设计泛型算法

### 普通特定类型算法

- 筛选出`vector<int>`中小于10的元素

  ```c++
  std::vector<int> less_than_ten(const std::vector<int>& vec){
      std::vector<int> res;
      for(std::vector<int>::const_iterator it=vec.begin();it!=vec.end();it++){//注意const_iterator
          if(*it<10){
              res.push_back(*it);
          }
      }
      return res;
  }
  ```

- 复用代码，实现筛选出`vector<int>`中小于10以及大于10的元素

  ```c++
  bool greater(const int& x,const int& y){
      return x>y?true:false;
  }
  
  bool less(const int& x,const int& y){
      return x<y?true:false;
  }
  
  std::vector<int> filter(const std::vector<int>& vec,int value,bool (*pred)(const int& x,const int& y)){
      std::vector<int> res;
      for(int i=0;i<vec.size();i++){
          if(pred(vec[i],value)){
              res.push_back(vec[i]);
          }
      }
      return res;
  }
  
  ```

- 求出`vector<int>`中元素为10的元素的个数

  ```c++
  int count_occurs(const std::vector<int>& vec,int val){
      std::vector<int>::const_iterator iter = vec.begin();
      int res=0;
      while((iter=find(iter,vec.end(),val))!=vec.end()){//注意迭代器的while写法
          res++;
          iter++;//++
      }
      return res;
  }
  ```



### function object

> 标准库中预先定义了一组function object，分为算术运算、关系运算、逻辑运算
>
> 要使用它们，需要首先包含其相关头文件
>
> `#include<functional>`

- function object的使用

  ```c++
  std::sort(init.begin(),init.end(),std::greater<int>()); //对vector中的元素按从大到小的顺序排列
  ```

- function object Adapter的使用

  ```c++
  //binder adapter 会将二元的function object转换为一元
  //标准库中有两个binder adapter：bind1st和bind2nd
  
  
  //重写filter实现小于10的元素筛选
  std::vector<int> filter(const std::vector<int>& vec,int value){
      std::vector<int> res;
      std::vector<int>::const_iterator iter = vec.begin();
      while((iter=find_if(iter,vec.end(),std::bind2nd(std::less<int>(),value)))!=vec.end()){
          res.push_back(*iter);
          iter++;
      }
      return res;
  }
  
  //重写filter实现可指定大于和小于元素的筛选，并实现泛型化
  template <typename InputIterator,typename OutputIterator,typename ElemType,typename Comp>
  OutputIterator filter(InputIterator first,InputIterator last,OutputIterator at,const ElemType& val,Comp pred){
      while((first=find_if(first,last,bind2nd(pred,val)))!=last){//pred可以为less<int>()等function object
          std::cout << *first << std::endl;
          *at = *first;
          at++;
          first++;
  
      }
      return at;
  }
  
  
  //negator adapter可以对function object的结果取反
  //not1用来对unary function object的值取反
  //not2用来对binary function object的值取反
  
  //筛选大于等于10的元素：unary 一元
  while((iter=find_if(iter,vec.end(),not1(bind2nd(less<int>,10))!=vec.end());
  ```

## Iterator Inserter的使用

> 所有设计到复制元素的算法：copy、copy_backwards、remove_copy、unique_coy等
>
> 每复制一个元素，都会被赋值，因此必须保证被复制的目的容器容量足够大。此时定义的目的容器的容量通常都是过大的。
>
> 标准库中提供了三个insertion adapter，用来避免使用赋值的方式；
>
> inserter不能用于array

- `back_inserter()`

  ```c++
  unique_copy(vec.begin(),vec.end(),back_inserter(nvec)); //unique_copy的第三个参数是至指定目的容器开始的地址
  //使用后，复制时会用容器的push_back替代赋值运算符
  ```

- `inserter()`

  ```c++
  unique_copy(vec.begin(),vec.end(),inserter(nvec,nvec.end()));
  //inserter有两个参数：容器名和插入容器的起点
  ```

- `front_insert()`

  ```c++
  //前插适用于list、deque等容器
  copy(list.begin(),list.end(),front_inserter(nlist));
  ```

  

## iostream inserter的使用

> 标准库中定义用于输入及输出的iostream iterator类有：istream_iterator、ostream_iterator
>
> 需要包含头文件 `#include<iterator>`

**利用iostream iterator从文件读取数**

```c++
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include<iterator>

int main()
{
    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");

    if(!in_file||!out_file){
        std::cerr << "open file error\n";
        return -1;
    }

    std::istream_iterator<std::string> is(in_file);
    std::istream_iterator<std::string> eof;
    std::vector<std::string> text;
    std::copy(is,eof,back_inserter(text));

    std::sort(text.begin(),text.end());

    std::ostream_iterator<std::string> os(out_file," ");
    std::copy(text.begin(),text.end(),os);

    return 0;
}
```



## Map的使用

> 头文件：`#include<map>`

map对象有一个名为first的member，对应于key；名为second的member，对应于value。

不存在的key，可以直接赋值的方法添加。

```c++
std::map<std::string,int> words;
std::string word;
while(std::cin >> word) words[word]++;
std::cout << words.size() << std::endl;
```

# Chapter04： 基于对象的编程风格

## Class的基本知识

1. 一般情况下：class由两部分组成，一组public操作函数和运算符，以及一组private实现细节

   -  public member可以在程序的任何地方被访问

   - private member只能在member function或者class friend内被访问

2. 如果一个member function在class主体内定义，会被自动视为inline function
3. class的定义及其inline function定义在头文件中，而non-inline function定义在程序文件中

## 构造函数与析构函数

- 定义class object的方式

  ```c++
  Triangular t; 		//调用默认的构造函数
  Triangular t1(10,3);//调用两个参数的构造函数
  Triangular t2 = 8;  //调用单一参数的构造函数！！！
  ```

- 构造函数的定义中，空参与默认参数的构造函数只能出现一种

  ```c++
  //空参
  Triangular(){
      //...
  }
  
  //默认参数：同时支持Triangular t;Triangular t(1);Triangular t(1,2); 三种定义方式
  Triangular(int len=1,int pos=1){
      //...
  }
  ```

- 参数列表初始化

  ```c++
  //优先使用参数列表初始化
  Triangular::Triangular(int len,int pos):_name("Triangluar"){
      _length = len > 0 ? len : 1; //不能直接用参数列表表达的放在函数体中初始化
      _pos = _pos > 0 > pos :1;
  }
  ```

- 析构函数

  ```c++
  //destructor并非一定需要
  ~Triangular(){
      delete [] _vector_object;
  }
  ```

- 拷贝构造函数

  ```c++
  //存在的原因：如果没有copy constructor
  Triangular t1(1);
  Triangular t2 = t1; //此时会自动逐一将t1中元素的值赋值给t2,如果t1中有heap中数据，t2会指向t1中相同的数据
  
  //重载一个copy constructor，自定义拷贝操作
  Triangular::Triangular(Triangular& t1){
      //...
  }
  
  //上面的情况只能通过Triangular t1(t);的方式定义，因此为了实现t1=t的形式，还需要重载=
  ```

  

## const与mutable

- 通过标明member function为const的方式，声明member function不会改变class object的内容

  ```c++
  class Triangular{
    int length() const {return _length}  //inline方式
    int elem(int pos) const;
  };
  
  int Triangular::elem(int pos) const{//声明和定义都要声明const
      return _elems[pos];
  }
  ```

- 当member function声明为function后，改变了某些成员变量，但是不影响class object的常量性时，可以将这些改变的成员变量声明为mutable

  ```c++
  class Triangular{
      public:
      	void next_reset() const {_next=_next-1;}
      private:
      	mutable int _next;
  }
  ```

  







# 繁杂知识点

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
- 了解到function object机制，用来代替运算符
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

  



----

---

















