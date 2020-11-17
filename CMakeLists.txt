cmake_minimum_required(VERSION 3.17)
project(Table_Drawing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -municode")
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lgdiplus")

add_executable(Table_Drawing main.cpp TableCell.h)