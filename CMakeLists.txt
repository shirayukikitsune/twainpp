cmake_minimum_required(VERSION 3.15)
project(twainpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find_package(Boost 1.71.0 REQUIRED date_time filesystem system)

add_subdirectory(src)
