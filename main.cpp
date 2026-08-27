#include <iostream>
#include <cstring>
#include <ncurses.h>
//#include <curses.h>
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
     // 1. Forza il terminale corretto per evitare che initscr fallisca
     /*
     Imposta la variabile d'ambiente che definisce l'identità del terminale. 
     Senza questa riga, l'ambiente di debug di VS Code non comunicava a ncurses quale tipo di schermo stesse usando, 
     impedendole di caricare le sequenze di escape corrette dal database di sistema (terminfo).
     */
     setenv("TERM", "xterm-256color", 1);


     //INIZIALIZZAZIONE
     setlocale(LC_ALL, "");
     initscr(); //inizializza lo schermo
     noecho(); //Non mostra il carattere della tastiera in input
     curs_set(0); //Nasconde il cursore
     refresh();

     BidirectionalList levelList;
     levelList.Create_Levels(); 

     // CHECKPOINT 1
     printw("1. Livelli creati correttamente!\n"); 
     refresh(); 
     getch(); // Aspetta che tu prema un tasto

     //2 CREAZIONE ENTITÀ
     Giocatore player(3, 1, 1);
     char input;

     // CHECKPOINT 2
     printw("2. Sto per chiamare posizionaGiocatoreStart...\n"); 
     refresh(); 
     getch();

     posizionaGiocatoreStart(player, levelList);

     if (levelList.getCurrent() == NULL || levelList.getCurrent()->level == NULL) {
          endwin();
          cout << "ERRORE CRITICO: Livello non caricato o lista vuota!" << endl;
          return 1;
     }

     // CHECKPOINT 3
     printw("3. Giocatore posizionato! Sto per chiamare stamp_map...\n"); 
     refresh(); 
     getch();

     //3 PRIMA STAMPA
     levelList.getCurrent()->level->stamp_map(player);

     // CHECKPOINT 4
     printw("4. Mappa stampata con successo!\n"); 
     refresh(); 
     getch();



     /*
     //Puntatore alla finestra window
     WINDOW *win = newwin(height, width, start_y, start_x);

     //Aggiorna lo schermo per farlo matchare a ciò c he è presente in memoria
     refresh();

     //Crea un bordo attorno alla window
     box(win, 0, 0);
     wrefresh(win);
     */

     // TEST

     //node* currentNode = levelList.getCurrent();
     //Map& m = currentNode->level->getMap();

     // 2. Variabili fittizie per far funzionare stamp_map (temporanee)
     //Giocatore player(3, 1, 1);
     //Nemico dummy_nemici[1];
     //Item dummy_items[1];
     //Bomba b;

     // 3. STAMPA IL LIVELLO!
     //m.stamp_map(player, dummy_nemici, 0, dummy_items, 0, b);
     //FINE TEST


       //Prende l'input dell'utente restituendo il valore int corrispondente al tasto premuto
      //getch();

      //Muove il cursore alle coordinate specificate
      //move(y, x);

      //dealloca la memoria e termina ncurses
      //endwin();





     //Giocatore player(3, 1, 1);
     //char input ;

     //posizionaGiocatoreStart( player, levelList ) ;


     //INIZIO CICLO
while ( player.vivo() ) {
     //1. leggi input
     input = getch();

     //2. esegui azione giocatore
     gestisciInput(player, levelList, input ) ;

     //3. controlla entrata / uscita
     controllaPassaggioLivelli( player, levelList ) ;

     player.aggiornaInvulnerabilita( ) ;

     bool colpito = levelList.updateLevels( player ) ;
     //4. aggiorna i timer dei potenziamenti dei livelli non correnti
     //+ aggiorna il livello corrente e ritorna true se il giocatore' ha subito danno
     //- nemici
     //- bomba
     //- collisioni

     if ( !colpito )
          levelList.getCurrent() -> level -> raccoltaItem( player ) ;

     levelList.getCurrent() -> level -> stamp_map( player ) ;

     if ( colpito ) {// il giocatore ha subito danno
          if ( player.vivo() ) {
               // mostra messaggio / animazione
               // "giocatore colpito, vite rimaste: x. tutte le bombe piazzate sono disattivate.
               // Invulnerabilita' attiva per x secondi"
               reset_v1 (player, levelList ) ;
          }
          else
               break ;

     }

     if ( levelList.isLastLevel( ) && levelList.getCurrent() -> level -> isCompletato( ))
          break ;
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


