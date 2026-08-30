#include "funzioni.h"
#include "Bomba.h"
#include "Map.hpp"
#include <cstdlib>
#include "BidirectionalList.hpp"
#include "Level.hpp"





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

    //Ho sostituito isWalkable() al posto di mossaValida()
    if ( lista_livelli.getCurrent() -> level -> getMap().isWalkable(temp) )
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


void posizionaGiocatoreStart( Giocatore& player, BidirectionalList& l ) {
    player.muovi( l.getCurrent() -> level -> getMap().getEntry()) ;
}


void controllaPassaggioLivelli( Giocatore& player, BidirectionalList& l ) {
    if ( l.getCurrent() -> level -> getMap().isEntry( player.getPosizione())) {
        if (l.goToPrev( ) ) //aggiorna il current della lista
            player.muovi( l.getCurrent() -> level -> getMap().getExit() ) ;
    }
    else if ( l.getCurrent() -> level -> getMap().isExit( player.getPosizione())) {
        if ( l.goToNext( )) //aggiorna il current della lista
            player.muovi(l.getCurrent() -> level -> getMap().getEntry() );
    }
    else
        return ;
}

void reset_v1( Giocatore& player, BidirectionalList& l) {
    l.reset_v1() ;
    player.invulnerabilitaOn() ;
}


