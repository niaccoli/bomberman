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

     int debug_contatore = 0;

     const int INTERVALLO_CICLO_MS = 100;
     const int TEMPO_AGGIORNAMENTO_NEMICI_MS = 1000 ;
     const int DURATA_PARTITA_MINUTI = 5 ;

     Timer timerGioco(DURATA_PARTITA_MINUTI * 60 * 1000) ;
     int timer_gioco = timerGioco.getTimer();
     Timer timerNemici (TEMPO_AGGIORNAMENTO_NEMICI_MS) ;

     //3 PRIMA STAMPA
     levelList.getCurrent()->level->stamp_map(player, timer_gioco);

     //INIZIO CICLO
     while ( player.vivo() && !timerGioco.scaduto( )) {
          //1. leggi input
          char temp;
          input = ERR;

          while ((temp = getch()) != ERR) //svuota la coda di input tenendo solo l'ultimo
               input = temp;


          if (input != ERR)
               gestisciInput(player, levelList, input);

          controllaPassaggioLivelli( player, levelList ) ;

          player.aggiornaInvulnerabilita( INTERVALLO_CICLO_MS ) ;

          levelList.updateBoostBombe(INTERVALLO_CICLO_MS ) ;


          bool colpito = false;

          if ( timerNemici.scaduto()) {
               levelList.moveEnemies( player ) ;
               timerNemici.attivaTimer(TEMPO_AGGIORNAMENTO_NEMICI_MS ) ;
          }

          colpito = levelList.collisioniGiocatoreNemici(player ) ;

          if ( !colpito )
			  colpito = levelList.updateBombs( player, INTERVALLO_CICLO_MS ) ;


          if (!colpito) {
               char tipo = levelList.getCurrent()->level->raccoltaItem(player);

               if (tipo != ' ')
                    levelList.applicaEffettoItem(player, tipo);
          }


          timer_gioco = timerGioco.getTimer();
          levelList.getCurrent() -> level -> stamp_map( player, timer_gioco );


          if ( colpito ) {// il giocatore ha subito danno
                if ( player.vivo() ) {
                         // mostra messaggio / animazione
                         // "giocatore colpito, vite rimaste: x. tutte le bombe piazzate sono disattivate.
                         // Invulnerabilita' attiva per x secondi"
                         reset_v3 (player, levelList ) ;
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

          timerNemici.diminuisci(INTERVALLO_CICLO_MS) ;
          timerGioco.diminuisci(INTERVALLO_CICLO_MS) ;

          napms(INTERVALLO_CICLO_MS) ;
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