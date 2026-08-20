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
        Bomba.h
        Item.h
        Item.cpp
        Bomba.cpp
        Nemico.cpp
        Nemico.h
        Personaggio.hpp
        Map.hpp
        Level.hpp
        Level.cpp
        Posizione.cpp
        Posizione.h
)

target_link_libraries(bomberman ${CURSES_LIBRARIES})

file(COPY level1.txt level2.txt level3.txt level4.txt level5.txt 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})