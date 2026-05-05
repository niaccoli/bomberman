cmake_minimum_required(VERSION 3.26)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses)
if(NOT CURSES_FOUND AND WIN32)
    set(CURSES_INCLUDE_DIR "C:/MinGW/include")
    set(CURSES_LIBRARIES "C:/MinGW/lib/libpdcurses.a")
endif ()
include_directories(${CURSES_INCLUDE_DIR})

add_executable(bomberman
        main.cpp
        Personaggio.cpp
        BidirectionalList.cpp
        Map.cpp
        funzioni.cpp
        Giocatore.cpp
        NemicoRandom.cpp
        NemicoInseguitore.cpp
        Bomba.h
        Item.h
        Item.cpp
        Bomba.cpp
)

target_link_libraries(bomberman ${CURSES_LIBRARIES})