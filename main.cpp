#include <iostream>
#include <cstring>
//#include <ncurses.h>
#include <curses.h>
#include "Map.hpp"
#include "BidirectionalList.hpp"
#include "funzioni.h"

using namespace std;



//dimensioni matrice: 25x70, con due righe e due colonne in più per i bordi.
const int width = 72;
const int height = 27;
char screen[height][width];


void menu(){
    
}

int main() {

    
    setlocale(LC_ALL, "");
    
    //inizializza lo schermo
    //setta la memoria e pulisce lo schermo (ncurses)
    initscr();
    noecho(); //Non mostra il carattere della tastiera in input
    curs_set(0); //Nasconde il cursore

    BidirectionalList levelList;

    levelList.Create_Levels(); //TEST

    int const start_y = 3;
    int const start_x = 5;


    /*
    //Puntatore alla finestra window
    WINDOW *win = newwin(height, width, start_y, start_x);

    //Aggiorna lo schermo per farlo matchare a ciò c he è presente in memoria
    refresh();

    //Crea un bordo attorno alla window
    box(win, 0, 0);
    wrefresh(win);
    */

    refresh();
    // TEST

    node* currentNode = levelList.getCurrent();
    Map& m = currentNode->level->getMap();

    // 2. Variabili fittizie per far funzionare stamp_map (temporanee)
    Giocatore player(3, 1, 1);
    Nemico dummy_nemici[1];
    Item dummy_items[1];
    Bomba b;

    // 3. STAMPA IL LIVELLO!
    m.stamp_map(player, dummy_nemici, 0, dummy_items, 0, b);
    //FINE TEST


    //Prende l'input dell'utente restituendo il valore int corrispondente al tasto premuto
    getch();

    //Muove il cursore alle coordinate specificate
    //move(y, x);

    //dealloca la memoria e termina ncurses
    //endwin();





   //Giocatore player(3, 1, 1);
     char input ;

     posizionaGiocatoreStart( player, levelList ) ;


   //INIZIO CICLO
while ( player.vivo() ) {
     //1. leggi input
     cin >> input ;

     //2. esegui azione giocatore
     gestisciInput(player, levelList, input ) ;

     //3. controlla entrata / uscita
     controllaPassaggioLivelli( player, levelList ) ;

     player.aggiornaInvulnerabilita( ) ;

     //4. aggiorna i timer dei potenziamenti dei livelli non correnti
     //+ aggiorna il livello corrente e ritorna true se il giocatore' ha subito danno
     //- nemici
     //- bomba
     //- collisioni
     if ( levelList.updateLevels( player ) /*mostra eventuale esplosione*/) {
          // il giocatore è stato colpito
          // mostra messaggio / animazione
          // gestisci perdita vita o riavvio del livello
          reset_v1 (player, levelList ) ;
     }
     else {
          //nessun danno subito dal giocatore
          levelList.getCurrent() -> level -> raccoltaItem( player ) ; //raccoglie gli item
          levelList.getCurrent() -> level -> stamp_map( player ) ; //stampa mappa
     }


//controlla fine partita
     //serve funzione: bool bidirectionalList::isLastLevel()
     //quindi controlliamo se e' l'ultimo livello ed e' completato (Level::isCompletato())
     //e nel caso cancelliamo l'ultimo nodo, mettiamo current a nullptr e break sul ciclo

}
     if ( player.vivo()) {
          //vittoria
     }
     else {
          //sconfitta
     }

     //dopo la fine della partita bisogna richiedere il nome del giocatore, sia in caso di vittoria che in caso di
     //sconfitta






    //set_border();
    //stamp_screen();

    endwin();


    return 0;
}


