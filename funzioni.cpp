#include "funzioni.h"
#include "Bomba.h"
#include "Map.hpp"
#include <cstdlib>
#include "BidirectionalList.hpp"
#include "Level.hpp"





void muoviGiocatore(Giocatore& player, BidirectionalList& lista_livelli, char input) {
    int dx = 0;
    int dy = 0;
    bool mossa_richiesta = true;

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
    //if ( lista_livelli.getCurrent() -> level -> getMap().isWalkable(temp) )
        //player.muovi( temp );

    if (mossa_richiesta) {
        Posizione temp = {player.getX() + dx , player.getY() + dy};
        Level* livello_corrente = lista_livelli.getCurrent()->level;

        // 1. Controlla se la mappa permette il passaggio (muri)
        bool calpestabile = livello_corrente->getMap().isWalkable(temp);

        // 2. Controlla se c'è una bomba attiva in quella posizione
        // (esattamente come fanno i nemici)
        bool bloccato_da_bomba = (livello_corrente->getBomb().innescata() && 
                                  stessaPosizione(temp, livello_corrente->getBomb().getPosizione()));

        // 3. Muovi il giocatore o cambia livello solo se è calpestabile E non c'è la bomba
        if (calpestabile && !bloccato_da_bomba) {

            player.muovi(temp);
            /*
            char destination_cell = livello_corrente->getMap().getCell(temp);

            if(destination_cell == 'U'){
                lista_livelli.goToNext();
                Level* new_level = lista_livelli.getCurrent()->level;
                Posizione pos_entry = new_level->getMap().getEntry();
                pos_entry.x = pos_entry.x + 1; 
                player.muovi(pos_entry);
            }
            else if(destination_cell == '@'){
                lista_livelli.goToPrev();
                Level* new_level = lista_livelli.getCurrent()->level;
                Posizione pos_exit = new_level->getMap().getExit();
                pos_exit.x = pos_exit.x - 1;
                player.muovi(pos_exit);
            }
            else
                player.muovi(temp);
            */
        }
    }

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
    Posizione p = l.getCurrent() -> level -> getMap().getEntry();
    p.x = p.x + 1;
    player.muovi(p);
}


void controllaPassaggioLivelli( Giocatore& player, BidirectionalList& l ) {
    if ( l.getCurrent() -> level -> getMap().isEntry( player.getPosizione())) {
        if (l.goToPrev( )){ //aggiorna il current della lista
            clear(); 
            refresh();

            Posizione pos_exit = l.getCurrent() -> level -> getMap().getExit();
            pos_exit.x = pos_exit.x - 1;
            player.muovi(pos_exit);
        }
    }
    else if ( l.getCurrent() -> level -> getMap().isExit( player.getPosizione())) {
        if ( l.goToNext( )){ //aggiorna il current della lista
            clear(); 
            refresh();

            Posizione pos_entry = l.getCurrent() -> level -> getMap().getEntry();
            pos_entry.x = pos_entry.x + 1;
            player.muovi(pos_entry);
        }
    }
    else
        return ;
}

void reset_v1( Giocatore& player, BidirectionalList& l) {
    l.reset_v1() ;
    player.invulnerabilitaOn() ;
}

void reset_v3(Giocatore& player, BidirectionalList& l ) {
    l.reset_v3( ) ;
    posizionaGiocatoreStart( player, l ) ;
}


int min(int n1, int n2, int n3, int n4 ) {

    int min = n1 ;

    if ( n2 < min)
        min = n2 ;

    if (n3 < min)
        min = n3 ;

    if ( n4 < min)
        min = n4 ;

    return min ;
}