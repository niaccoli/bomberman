cmake_minimum_required(VERSION 3.26)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(bomberman
        main.cpp
        Player.cpp
        BidirectionalList.cpp
        Map.cpp
)

target_link_libraries(bomberman ${CURSES_LIBRARIES})