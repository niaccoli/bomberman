#ifndef MAP_HPP
#define MAP_HPP
#include <curses.h>
#include "Personaggio.hpp"
#include "Nemico.h" //Aggiungere la calsse nemica generale!!!!!!!!!!!!!!!!!
#include "Bomba.h"
#include "Item.h"

class Nemico ; //Forward declaration perche': Map.hpp usa il tipo Nemico, ma non sa ancora che esiste.


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

    //Andrea:
    bool isWalkable (Posizione posizione ) ; //ritorna true se la cella non e' un muro

    //Andrea
    Posizione walkableRandomPosition( ) ; //ritorna una posizione randomica camminabile(senza muri) nella mappa

    //Andrea:
    void breakWall(Posizione posizione) ;

    //Andrea:
    bool isBreakable( Posizione posizione ) ; //ritorna true se e' un muro distruttibile

    bool isUnbreakableWall ( Posizione posizione ) ; //ritorna true se e' un muro indistruttibile

    WINDOW* getWin();

    //ANDREA:
    //
};
#endif