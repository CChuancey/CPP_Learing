cmake_minimum_required(VERSION 3.16)

project(CPP_Learning)
aux_source_directory(./src SRC_LIST)
include_directories(C:\\Mingw\\include\\boost_1_78_0\\boost_1_78_0)



add_executable(main ./src/main.cpp)
add_executable(class01 ./src/class01.cpp)
add_executable(contanier ./src/contanier.cpp)
add_executable(ptr ./src/ptr.cpp)
add_executable(DesignPatterns01_Simple_Factory ./src/DesignPatterns01_Simple_Factory.cpp)
add_executable(DesignPatterns01_Factory ./src/DesignPatterns01_Factory.cpp)
add_executable(DesignPatterns01_AbstractFactory ./src/DesignPatterns01_AbstractFactory.cpp)
add_executable(DesignPatterns02_SingleInstance ./src/DesignPatterns02_SingleInstance.cpp)
add_executable(DesignPatterns03_Proxy ./src/DesignPatterns03_Proxy.cpp)
add_executable(DesignPatterns04_Decorate ./src/DesignPatterns04_Decorate.cpp)
add_executable(DesignPatterns05_Appearance ./src/DesignPatterns05_Appearance.cpp)
add_executable(DesignPatterns06_Adapter ./src/DesignPatterns06_Adapter.cpp)
add_executable(DesignPatterns07_Command ./src/DesignPatterns07_Command.cpp)
add_executable(DesignPatterns08_Strategy ./src/DesignPatterns08_Strategy.cpp)
add_executable(DesignPatterns09_Observer ./src/DesignPatterns09_Observer.cpp)
add_executable(cppKeywords ./src/cppKeywords.cpp)
add_executable(sharedptr ./src/sharedptr.cpp)
add_executable(lambda ./src/lambda.cpp)
add_executable(stl ./src/stl.cpp)
add_executable(thread ./src/thread.cpp)
target_link_libraries(thread pthread)
add_executable(net ./src/net.cpp)
target_link_libraries(net pthread)

add_definitions(-std=c++11)

