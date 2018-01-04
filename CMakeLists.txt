cmake_minimum_required(VERSION 3.9)
project(primetester)

set(CMAKE_CXX_STANDARD 11)

add_executable(primetester main.cpp tcpconnection.cpp tcpconnection.h)
target_link_libraries(primetester ws2_32)

add_subdirectory(gtest-external)
add_subdirectory(automated-tests)