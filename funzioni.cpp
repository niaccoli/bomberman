#include "funzioni.hpp"
#include "Bomba.hpp"
#include "Mappa.hpp"
#include <cstdlib>
#include "ListaBidirezionale.hpp"
#include "Livello.hpp"





void muoviGiocatore(Giocatore& player, ListaBidirezionale& lista_livelli, char input) {
    int dx = 0;
    int dy = 0;
    bool mossa_richiesta = true;

    if (input == 'w' || input == 'W')
        dy = -1;
    else if (input == 'a' || input == 'A')
        dx = -1;
    else if (input == 's' || input == 'S')
        dy = 1;
    else
        dx = 1;

    Posizione temp = {player.getX() + dx , player.getY() + dy};

    if (mossa_richiesta) {
        Posizione temp = {player.getX() + dx , player.getY() + dy};
        Livello* livello_corrente = lista_livelli.getCurrent()->level;

        // 1. Controlla se la mappa permette il passaggio (muri)
        bool calpestabile = livello_corrente->getMap().isCamminabile(temp);

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



void gestisciInput(Giocatore& player,ListaBidirezionale& lista_livelli, char input) {
    if (input == 'W' || input == 'w' || input == 'A' || input == 'a' || input == 's' || input == 'S' ||
        input == 'd' || input == 'D')
        muoviGiocatore(player, lista_livelli, input);
    else if (input == 'x' || input == 'X') {
        lista_livelli.getCurrent() -> level -> piazzaBomba(player ) ;
    }
    else
        return;
}




void posizionaGiocatoreStart( Giocatore& player, ListaBidirezionale& l ) {
    Posizione p = l.getCurrent() -> level -> getMap().getEntrata( );
    p.x = p.x + 1;
    player.muovi(p);
}


void controllaPassaggioLivelli( Giocatore& player, ListaBidirezionale& l ) {
    if ( l.getCurrent() -> level -> getMap().isEntrata( player.getPosizione())) {
        if (l.goToPrev( )){ //aggiorna il current della lista
            clear(); 
            refresh();

            Posizione pos_exit = l.getCurrent() -> level -> getMap().getUscita();
            pos_exit.x = pos_exit.x - 1;
            player.muovi(pos_exit);
        }
    }
    else if ( l.getCurrent() -> level -> getMap().isUscita( player.getPosizione())) {
        if ( l.goToNext( )){
            clear(); 
            refresh();

            Posizione pos_entry = l.getCurrent() -> level -> getMap().getEntrata();
            pos_entry.x = pos_entry.x + 1;
            player.muovi(pos_entry);
        }
    }
    else
        return ;
}

void reset_v1( Giocatore& player, ListaBidirezionale& l) {
    l.reset_v1() ;
    player.invulnerabilitaOn() ;
}

void reset_v3(Giocatore& player, ListaBidirezionale& l ) {
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

void popupGiocatoreColpito(){

    clear();
    refresh();
    
    int h_finestra_popup = 7;
    int w_finestra_popup = 42;
    int pop_y = (LINES - h_finestra_popup) / 2;
    int pop_x = (COLS - w_finestra_popup) / 2;

    WINDOW* colpito_win = newwin(h_finestra_popup, w_finestra_popup, pop_y, pop_x);

    wbkgd(colpito_win, COLOR_PAIR(2));
    box(colpito_win, 0, 0);

    wattron(colpito_win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(colpito_win, 2, (w_finestra_popup - 20) / 2, "GIOCATORE COLPITO!");
    mvwprintw(colpito_win, 4, (w_finestra_popup - 30) / 2, "Tutte le bombe disinnescate");
    mvwprintw(colpito_win, 5, (w_finestra_popup - 27) / 2, "e potenziamenti resettati");
    wattroff(colpito_win, COLOR_PAIR(2) | A_BOLD);

    wrefresh(colpito_win);

    napms(1500);
    werase(colpito_win);
    wrefresh(colpito_win);
    delwin(colpito_win);
}

void StampaInfo(const Giocatore& player,const Bomba& b, int timer_gioco, Posizione mappa_schermo){

     int start_x = mappa_schermo.x + 5;
     int start_y = mappa_schermo.y + 2;

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
     int points = player.getPunteggio();
     mvprintw(start_y + 3, start_x, "Tempo rimasto: %02d:%02d   ", minute, seconds);
     mvprintw(start_y + 4, start_x, "Punteggio: %-4d", points);

     // 3. POTENZIAMENTI ATTIVI
     mvprintw(start_y + 6, start_x, "--- POTENZIAMENTI ---");
    
     int riga = start_y + 7;

     int timer_item = 0;

     // Usiamo i metodi che hai già scritto nella classe Bomba!
     if (b.potenziamentoDannoAttivo()) {
        timer_item = b.getDurataPotenziamentoDanno() / 1000;
        int item_seconds = timer_item % 60;
        mvprintw(riga++, start_x, "Danno Extra  [%02d]  ", item_seconds);
     }
     if (b.potenziamentoRaggioAttivo()) {
        timer_item = b.getDurataPotenziamentoRaggio() / 1000;
        int item_seconds = timer_item % 60;
        mvprintw(riga++, start_x, "Raggio Extra [%02d]  ", item_seconds);
     }
     if (b.potenziamentoTimerAttivo()) {
        timer_item = b.getDurataPotenziamentoTimer() / 1000;
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