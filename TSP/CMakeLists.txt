cmake_minimum_required(VERSION 3.10)
project(app)

set(CMAKE_CXX_STANDARD 17)

add_executable(app
    main.cpp
    opener.cpp
    anealling.cpp
)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(MPI REQUIRED)

target_link_libraries(app
    sfml-graphics
    sfml-window
    sfml-system
    MPI::MPI_CXX
)
