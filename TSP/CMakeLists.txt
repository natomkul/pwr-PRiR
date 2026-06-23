cmake_minimum_required(VERSION 3.10)
project(app)

set(CMAKE_CXX_STANDARD 17)

add_executable(tests
    main.cpp
    opener.cpp
    anealling.cpp
)

add_executable(visual
    main_visual.cpp
    opener.cpp
    anealling.cpp
)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(MPI REQUIRED)

target_link_libraries(tests
    MPI::MPI_CXX
)

target_link_libraries(visual
    sfml-graphics
    sfml-window
    sfml-system
)
