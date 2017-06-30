project(thodd-cpp-tests CXX)
cmake_minimum_required(VERSION 3.8.0-rc4)

set(CMAKE_C_COMPILER   gcc)
set(CMAKE_CXX_COMPILER g++)

install(DIRECTORIES "include" DESTINATION ${CMAKE_INCLUDE_PATH})