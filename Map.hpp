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
    Posizione entry ;
    Posizione exit ;

public:
    //costruttore
    Map(int h, int w);

    char getCell(int x, int y);

    void setCell(int x, int y, char c);

    void Initialize_Map(int levelID);
    
    //Metodo stamp map vecchio
    void stamp_map(const Personaggio& p, const Nemico nemici[], int numNemici, const Item items[], int numItems, const Bomba& b );

    void stamp_map(const Personaggio& p, const Nemico nemici[], int numNemici, const Item items[], int numItems,
        const Bomba& b , Posizione celle_esplosione[], int num_celle_esplosione);

    bool mossavalida(int x, int y); //forse cancelare o chiamare isWalkable perche' alla fine la mossa e' valida se la cella
    //non e' un muro

    //Matteo: metodo cancellabile siccome lo hai messo tu con il paramentro posizione
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

    int getRows();

    int getCols();

    bool cell_without_wall(int x, int y);

    WINDOW* getWin();

    Posizione getEntry( ) ;

    Posizione getExit ( ) ;

    bool isEntry( Posizione posizione) ;

    bool isExit( Posizione posizione) ;

    bool isNearEntry( Posizione posizione ) ;

};
#endif