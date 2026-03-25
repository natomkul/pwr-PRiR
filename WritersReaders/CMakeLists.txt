cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ReadersWriters)

add_executable(ReadersWriters main.cpp book.cpp wrapper.cpp writer.cpp reader.cpp)

