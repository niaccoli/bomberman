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

void StampInfo(const Giocatore& player,const Bomba& b, int map_cols, int timer_gioco){
     int start_x = map_cols + 5;
     int start_y = 2;

     int total_time_in_seconds = timer_gioco / 1000;

     int minute = total_time_in_seconds / 60;
     int seconds = total_time_in_seconds % 60;

     attron(A_BOLD);
     mvprintw(start_y, start_x, "=== STATISTICHE ===");
     attroff(A_BOLD);

     // 1. VITE
     attron(COLOR_PAIR(4) | A_BOLD);
     // Usiamo %-3d per allineare i numeri e cancellare i residui (es. da 10 a 9)
     mvprintw(start_y + 2, start_x, "Vite: %-3d", player.getVite()); 
     attroff(COLOR_PAIR(4) | A_BOLD);

     // 2. PUNTEGGIO E TEMPO (Aggiungi qui i tuoi getter se li hai)
     char points = player.getPunteggio();
     mvprintw(start_y + 3, start_x, "Tempo rimasto: %02d:%02d   ", minute, seconds);
     mvprintw(start_y + 4, start_x, "Punteggio: %-4d", points);

     // 3. POTENZIAMENTI ATTIVI
     mvprintw(start_y + 6, start_x, "--- POTENZIAMENTI ---");
    
     int riga = start_y + 7;

     int timer_item = 0;

     // Usiamo i metodi che hai già scritto nella classe Bomba!
     if (b.boostDannoAttivo()) {
        timer_item = b.getDurataBoostDanno() / 1000;
        int item_seconds = timer_item % 60;
        mvprintw(riga++, start_x, "Danno Extra  [%02d]  ", item_seconds);
     }
     if (b.boostRaggioAttivo()) {
        timer_item = b.getDurataBoosRaggio() / 1000;
        int item_seconds = timer_item % 60;
        mvprintw(riga++, start_x, "Raggio Extra [%02d]  ", item_seconds);
     }
     if (b.boostTimerAttivo()) {
        timer_item = b.getDurataBoostTimer() / 1000;
        int item_seconds = timer_item % 60;
        mvprintw(riga++, start_x, "Bomba Veloce [%02d]  ", item_seconds);
     }

     // PULIZIA EFFETTO FANTASMA: Se un potenziamento scade, cancella la riga rimasta!
     // Stampiamo un po' di spazi vuoti nelle righe successive
     for (int i = 0; i < 3; i++) {
          mvprintw(riga++, start_x, "                       "); 
     }

     refresh(); // Aggiorna lo schermo base per mostrare le scritte
}