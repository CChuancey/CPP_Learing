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



## VS Code使用CMake工具编译调试 

> 在完成基本的C++开发环境配置后，进行单个文件的调试运行是比较方便的。但是遇到了多文件的项目，就会出现编译失败的问题。cmake是一个可以用在大型项目中的makefile生成工具，可以很方便的进行多文件的调试编译。

1. 安装cmake工具：https://cmake.org/download/ 在安装的过程中选择自动配置环境变量

2. 在VS Code中安装C/C++ 、CMake、 CMakeTool三个插件

3. 新建项目，编写源代码，按F5，生成launch.json和task.json两个文件。

4. 新建CMakeLists.txt文件，并加入编译参数，例如：

   ```cmake
   project(test)
   
   add_executable(main main.cpp)
   ```

5. Ctrl+Shift+P调出命令面板，输入cmake，选择configure，选择gcc编译器目录，会自动生成cmake编译环境（build文件夹）

6. 修改launch.json中的program字段：目录中加build；同时,cwd和program字段的目录修改为workspace

   ```json
   {
       // Use IntelliSense to learn about possible attributes.
       // Hover to view descriptions of existing attributes.
       // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
       "version": "0.2.0",
       "configurations": [
           {
               "name": "g++.exe - 生成和调试活动文件",
               "type": "cppdbg",
               "request": "launch",
               "program": "${workspaceFolder}\\build\\${fileBasenameNoExtension}.exe", //生成的二进制文件在build文件夹下
               "args": [],
               "stopAtEntry": false,
               "cwd": "${workspaceFolder}",
               "environment": [],
               "externalConsole": false,
               "MIMode": "gdb",
               "miDebuggerPath": "C:\\mingw-w64\\x86_64-8.1.0-win32-seh-rt_v6-rev0\\mingw64\\bin\\gdb.exe",
               "setupCommands": [
                   {
                       "description": "为 gdb 启用整齐打印",
                       "text": "-enable-pretty-printing",
                       "ignoreFailures": true
                   }
               ],
               "preLaunchTask": "C/C++: g++.exe 生成活动文件"
           }
       ]
   }
   ```

7. 替换现有的task.json

   ```json
   {   
       "version": "2.0.0",
       "options": {
           "cwd": "${workspaceFolder}/build"
       },
       "tasks": [
           {
               "type": "shell",
               "label": "cmake",
               "command": "cmake",
               "args": [
                   ".."
               ],
           },
           {
               "label": "make",
               "group": {
                   "kind": "build",
                   "isDefault": true
               },
               "command": "mingw32-make",
               "args": [
   
               ],
           },
           {
               "label": "C/C++: g++.exe 生成活动文件",
               "dependsOn":[
                   "cmake",
                   "make"
               ]
           }
       ],
   
   }
   ```

   









