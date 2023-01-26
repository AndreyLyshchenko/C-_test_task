cmake_minimum_required(VERSION 3.22)

set(CXX_STANDARD C++20)

project(test)

find_package(Threads)

add_executable(test Main.cpp DelayedTask.cpp SimpleTask.cpp task.cpp CustomLess.cpp)

target_link_libraries(test Threads::Threads)