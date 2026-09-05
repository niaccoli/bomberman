#include <iostream>
#include <cstring>
//#include <ncurses.h>
#include <curses.h>
#include "Map.hpp"
#include "BidirectionalList.hpp"
#include "funzioni.h"
#include "Timer.h"

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
     //setenv() è una funzione tipica dei sistemi POSIX/Linux e non è disponibile normalmente nella compilazione nativa
     //Windows con MinGW.


     #ifdef _WIN32
          // Su Windows con PDCurses non è necessario impostare TERM
     #else
          setenv("TERM", "xterm-256color", 1);
     #endif
     /*La logica è:

     Windows
     → usa PDCurses nativa
     → non esegue setenv()

     Linux/macOS
     → esegue setenv("TERM", ...)*/


     //INIZIALIZZAZIONE
     setlocale(LC_ALL, "");
     initscr(); //inizializza lo schermo
     noecho(); //Non mostra il carattere della tastiera in input
     curs_set(0); //Nasconde il cursore

     timeout(0);

     refresh();

     if (has_colors()) {
          start_color();
          use_default_colors(); // Mantiene lo sfondo trasparente/predefinito del terminale

          // init_pair(ID_COPPIA, COLORE_TESTO, COLORE_SFONDO);
          init_pair(1, COLOR_CYAN,    -1); // Giocatore
          init_pair(2, COLOR_RED,     -1); // Nemici / Bomba
          init_pair(3, COLOR_YELLOW,  -1); // Bomba
          init_pair(4, COLOR_GREEN,   -1); // Item / Valuta
          init_pair(5, COLOR_WHITE,   -1); // Muri indistruttibili
          init_pair(6, COLOR_RED,  COLOR_RED);   // Esplosione
     }

     BidirectionalList levelList;
     levelList.Create_Levels(); 

     //2 CREAZIONE ENTITÀ
     Giocatore player(3, 1, 1);
     char input;

     posizionaGiocatoreStart(player, levelList);

     //3 PRIMA STAMPA
     levelList.getCurrent()->level->stamp_map(player);

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

     // Prima del while, dichiara un contatore
     int debug_contatore = 0;


     Timer timerGioco(300000) ;
     Timer timerNemici (1000) ;
     Timer timerBombe (100);
     Timer timerInvulnerabilita (100) ;


     //INIZIO CICLO
     while ( player.vivo() && !timerGioco.scaduto( )) {
          //1. leggi input
          char temp;
          input = ERR;

          while ((temp = getch()) != ERR) //svuota la coda di input tenendo solo l'ultimo
               input = temp;

          if (input != ERR)
               gestisciInput(player, levelList, input);

          if(input != ERR){
               //2. esegui azione giocatore
               gestisciInput(player, levelList, input ) ;
          }

          controllaPassaggioLivelli( player, levelList ) ;

          if ( timerInvulnerabilita.scaduto()) {
               player.aggiornaInvulnerabilita( ) ;
               timerInvulnerabilita.attivaTimer(100) ;
          }


          bool colpito = false;

          if ( timerNemici.scaduto()) {
               colpito = levelList.updateEnemies( player ) ;
               timerNemici.attivaTimer(1000 ) ;
          }


          if ( !colpito && timerBombe. scaduto() ){

			  colpito = levelList.updateBombs( player ) ;
			  timerBombe.attivaTimer(100) ;
		}


          if (!colpito) {
               char tipo = levelList.getCurrent()->level->raccoltaItem(player);

               if (tipo != ' ')
                    levelList.applicaEffettoItem(player, tipo);
          }

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

          // --- AGGIUNGI QUESTE TRE RIGHE ALLA FINE DEL WHILE ---
          debug_contatore++;
          mvprintw(0, 0, "Battito loop: %d | Ultimo input: %d", debug_contatore, input);
          refresh(); // Questo aggiorna lo sfondo, separato dalla mappa

          timerNemici.diminuisci(100) ;
	     timerBombe.diminuisci(100) ;
          timerGioco.diminuisci(100) ;
          timerInvulnerabilita.diminuisci(100);

          napms(100) ;
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