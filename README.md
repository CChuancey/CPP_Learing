# CPP_Learing

> 暂定学习路线：
>
> - Essential C++
> - C++ Primer 第五版
> - Effective C++



## 用VS Code配置C++开发环境

1. 下载vscode

2. 下载mingw installer：https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/

3. 安装mingw 编译器

   ![preview](https://pic1.zhimg.com/v2-3aae1eb09e5b78b306706ee3ed8693ac_r.jpg)

4. 配置环境变量：将编译器安装目录加入到环境变量中

5. gcc -v验证环境变量是否配置成功

6. 配置VS code的编译环境

   - 使用快捷键Ctrl+Shift+P调出命令面板，输入C/C++，选择“Edit Configurations(UI)”，编译器路径中选择g++编译器，IntelliSense选择gcc-x64。此时会生成c_cpp_properties.json文件
   - 使用快捷键Ctrl+Shift+P调出命令面板，输入tasks，选择“Tasks:Configure Default Build Task”，再选择g++。此时会生成task.json文件
   - 点击菜单栏运行-->启动调试-->选择C++(GDB/LLDB)。此时会生成launch.json文件













