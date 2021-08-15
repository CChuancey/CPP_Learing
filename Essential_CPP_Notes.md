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





























