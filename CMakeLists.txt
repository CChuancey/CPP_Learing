cmake_minimum_required(VERSION 3.0)

project(CPP_Learning)
aux_source_directory(./src SRC_LIST)

add_executable(main ./src/main.cpp)
add_executable(class01 ./src/class01.cpp)
add_definitions(-std=c++11)

