cmake_minimum_required(VERSION 3.0)

project(CPP_Learning)
aux_source_directory(./src SRC_LIST)

add_executable(main ./src/main.cpp)
add_executable(class01 ./src/class01.cpp)
add_executable(contanier ./src/contanier.cpp)
add_executable(ptr ./src/ptr.cpp)
add_executable(DesignPatterns01_Simple_Factory ./src/DesignPatterns01_Simple_Factory.cpp)
add_executable(DesignPatterns01_Factory ./src/DesignPatterns01_Factory.cpp)
add_executable(DesignPatterns01_AbstractFactory ./src/DesignPatterns01_AbstractFactory.cpp)
add_definitions(-std=c++11)

