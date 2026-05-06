#ifndef MAP_HPP
#define MAP_HPP
#include <curses.h>
#include "Personaggio.hpp"

class Map{
protected:
    int rows;
    int cols;
    char** grid;
    WINDOW* win;

public:
    //costruttore
    Map(int h, int w, int start_y, int start_x);

    void Initialize_Map(int levelID);
    
    void stamp_map();

    bool isWalkable(int x, int y);

    void breakWall();

    WINDOW* getWin();
};
#endif