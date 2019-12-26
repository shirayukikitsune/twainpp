cmake_minimum_required(VERSION 3.15)
project(twainpp)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost 1.71.0 REQUIRED filesystem system)

add_subdirectory(src)
add_subdirectory(test)
