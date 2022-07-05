cmake_minimum_required(VERSION 3.16)
project(ForkSTL)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(
    ForkSTL
        ForkList.hpp
        ForkQueue.hpp
        ForkVector.hpp
        main.cpp 
        ForkStack.hpp
)
