#include "funzioni.h"
#include "Bomba.h"
#include "Map.hpp"
#include <cstdlib>
#include "BidirectionalList.hpp"
#include "Level.hpp"


//da implementare con Posizione
void muoviGiocatore(Giocatore& player, BidirectionalList& lista_livelli, char input) {
    int dx = 0;
    int dy = 0;

    if (input == 'w' || input == 'W')
        dy = -1;
    else if (input == 'a' || input == 'A')
        dx = -1;
    else if (input == 's' || input == 'S')
        dy = 1;
    else //chat suggerisce di aggiungere un if esle e un else con return (valutare: in realtà il controllo lo faccio gia sotto)
        dx = 1;

    Posizione temp = {player.getX() + dx , player.getY() + dy};

    if ( lista_livelli.getCurrent() -> level -> getMap().mossavalida(temp.x, temp.y) )
        player.muovi( temp );
}



void gestisciInput(Giocatore& player,BidirectionalList& lista_livelli, char input) {
    if (input == 'W' || input == 'w' || input == 'A' || input == 'a' || input == 's' || input == 'S' ||
        input == 'd' || input == 'D')
        muoviGiocatore(player, lista_livelli, input);
    else if (input == 'x' || input == 'X') {
        lista_livelli.getCurrent() -> level -> piazzaBomba(player ) ;
    }
    else
        return;
}





