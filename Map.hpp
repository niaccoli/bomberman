#ifndef MAP_HPP
#define MAP_HPP
#include <curses.h>
#include "Personaggio.hpp"
#include "Nemico.hpp". //Aggiungere la calsse nemica generale!!!!!!!!!!!!!!!!!
#include "Bomba.h"
#include "Item.h"


class Map{
protected:
    int rows;
    int cols;
    char** grid;
    WINDOW* win;

public:
    //costruttore
    Map(int h, int w, int start_y, int start_x);

    char getCell(int x, int y);

    void setCell(int x, int y, char c);

    void Initialize_Map(int levelID);
    
    void stamp_map(const Personaggio& p, const Nemico nemici[], int numNemici, const Item items[], int numItems, const Bomba& b );

    bool mossavalida(int x, int y);

    void breakWall();

    WINDOW* getWin();
};
#endif