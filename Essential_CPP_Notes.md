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

  

