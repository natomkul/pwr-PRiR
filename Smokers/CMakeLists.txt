cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Smokers)

add_executable(Smokers main.cpp smoker.cpp logger.cpp tamper.cpp matches.cpp)

