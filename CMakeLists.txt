cmake_minimum_required(VERSION 3.26)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses)
if(NOT CURSES_FOUND AND WIN32)
    if(EXISTS "C:/msys64/mingw64/include/pdcurses/curses.h")
        set(CURSES_INCLUDE_DIR "C:/msys64/mingw64/include/pdcurses")
        set(CURSES_LIBRARIES "C:/msys64/mingw64/lib/libpdcurses_wincon.a")
        set(USE_MSYS2_PDCURSES TRUE)

    elseif(EXISTS "C:/MinGW/include/curses.h")
        set(CURSES_INCLUDE_DIR "C:/MinGW/include")
        set(CURSES_LIBRARIES "C:/MinGW/lib/libpdcurses.a")

    else()
        message(FATAL_ERROR "PDCurses non trovata")
    endif ()

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
        Timer.cpp
        Timer.h
)

if(USE_MSYS2_PDCURSES)
    target_compile_definitions(bomberman PRIVATE PDC_WIDE=1 PDC_FORCE_UTF8=1)
endif()

target_link_libraries(bomberman ${CURSES_LIBRARIES})

if(USE_MSYS2_PDCURSES)
    target_link_libraries(bomberman winmm)
endif()

file(COPY level1.txt level2.txt level3.txt level4.txt level5.txt 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})