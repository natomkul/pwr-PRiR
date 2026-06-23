cmake_minimum_required(VERSION 3.10)
project(server)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(server server.cpp ${SOURCES})

target_include_directories(server PRIVATE src)

