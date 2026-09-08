#include <iostream>
#include <cstring>
//#include <ncurses.h>
#include <curses.h>
#include "Mappa.hpp"
#include "ListaBidirezionale.hpp"
#include "funzioni.h"
#include "Timer.h"
#include "Classifica.h"
#include "Menu.h"
#include <cstdlib>

using namespace std;


int main() {

     #ifdef _WIN32
          // Su Windows con PDCurses non è necessario impostare TERM
     #else
          setenv("TERM", "xterm-256color", 1);
     #endif

     //INIZIALIZZAZIONE
     setlocale(LC_ALL, "");
     initscr(); //crea automaticamente una finestra che rappresenta tutto il terminale. (chiamata stdscr)
     noecho(); //Non mostra il carattere della tastiera in input
     curs_set(0); //Nasconde il cursore



     Classifica classifica ;
     classifica.caricaDaFile_v2() ;
     Menu menu ;

     timeout(-1) ;
     menu.stampa() ;


     while (menu.leggiInput() != '\n') {
     }

     int selezione = menu.getSelezione();


     while ( selezione != 3 ) {
          if ( selezione == 0) {
               timeout(0); //importante per il gameLoop altrimenti getch(); poptrebbe aspettare finche' l'utente non preme un testo

               clear() ;
               refresh();



               if (has_colors()) { //controlla se il terminale supporta i colori
                    start_color(); //abilita il sistema di colori curses.
                    use_default_colors(); // Mantiene lo sfondo trasparente/predefinito del terminale

                    // init_pair(ID_COPPIA, COLORE_TESTO, COLORE_SFONDO); (-1) usa il. default del terminale
                    init_pair(1, COLOR_CYAN,    -1);        // Giocatore
                    init_pair(2, COLOR_RED,     -1);        // Nemici / Bomba
                    init_pair(3, COLOR_YELLOW,  -1);        // Bomba
                    init_pair(4, COLOR_GREEN,   -1);        // Item
                    init_pair(5, COLOR_WHITE,   -1);        // Muri indistruttibili
                    init_pair(6, COLOR_RED,  COLOR_RED);    // Esplosione
               }

               ListaBidirezionale levelList;
               levelList.CreaLivelli();

               //2 CREAZIONE ENTITÀ
               Giocatore player(3, 1, 1);

               posizionaGiocatoreStart(player, levelList);




               const int INTERVALLO_CICLO_MS = 100;
               const int TEMPO_AGGIORNAMENTO_NEMICI_MS = 1000 ;
               const int DURATA_PARTITA_MINUTI = 5 ;

     Timer timerGioco(DURATA_PARTITA_MINUTI * 60 * 1000) ;
     int timer_gioco = timerGioco.getTimer();
     Timer timerNemici (TEMPO_AGGIORNAMENTO_NEMICI_MS) ;

     //3 PRIMA STAMPA
     levelList.getCurrent()->level->stampaMappa(player, timer_gioco);

               //INIZIO CICLO
               while ( player.vivo() && !timerGioco.scaduto( )) {
                    //1. leggi input
                    char temp; //sarebbe meglio int (valutare)
                    char input = ERR;

                    while ((temp = getch()) != ERR) //svuota la coda di input tenendo solo l'ultimo
                         input = temp;
                    //legge un tasto dalla tastiera.
                    //legge un tasto dalla tastiera.
                    //Il comportamento dipende da timeout
                    //timeout(-1)= aspetta per sempre
                    //timeout(0)=non aspettare, se non viene premuto niente ritorni ERR
                    //timeout(x)= aspetta x ms, se non viene premuto niente ritorni ERR

                    if (input != ERR)
                         gestisciInput(player, levelList, input);

                    controllaPassaggioLivelli( player, levelList ) ;

                    player.aggiornaInvulnerabilita( INTERVALLO_CICLO_MS ) ;

                    levelList.updateBoostBombe(INTERVALLO_CICLO_MS ) ;


                    bool colpito = false;

                    if ( timerNemici.scaduto()) {
                         levelList.muoviNemici( player ) ;
                         timerNemici.attivaTimer(TEMPO_AGGIORNAMENTO_NEMICI_MS ) ;
                    }

                    colpito = levelList.collisioniGiocatoreNemici(player ) ;

                    if ( !colpito )
                         colpito = levelList.aggiornaBomba( player, INTERVALLO_CICLO_MS ) ;


                    if (!colpito) {
                         char tipo = levelList.getCurrent()->level->raccoltaItem(player);

                         if (tipo != ' ')
                              levelList.applicaEffettoItem(player, tipo);
                    }


          timer_gioco = timerGioco.getTimer();
          levelList.getCurrent() -> level -> stampaMappa( player, timer_gioco );


          if ( colpito ) {// il giocatore ha subito danno
                if ( player.vivo() ) {
                    popupGiocatoreColpito();
                    reset_v3 (player, levelList );
                }
                else
                    break ;
               }

                    if ( levelList.isUltimoLivello( ) && levelList.getCurrent() -> level -> isCompletato( ))
                         break ;


                    refresh(); // Questo aggiorna lo sfondo, separato dalla mappa


                    timerNemici.diminuisci(INTERVALLO_CICLO_MS) ;
                    timerGioco.diminuisci(INTERVALLO_CICLO_MS) ;

                    napms(INTERVALLO_CICLO_MS) ;
               }



               char nome[100];

               timeout(-1);

               clear();

               if (player.vivo()) {
                    player.aumentaPunteggio(timerGioco.getTimer() / 1000);
                    mvprintw(1, 1, "HAI VINTO!");
               }
               else
                    mvprintw(1, 1, "GAME OVER");

               mvprintw(3, 1, "Punteggio: %d", player.getPunteggio());
               mvprintw(5, 1, "Inserisci nome: ");

               echo();
               curs_set(1);

               refresh();

               getnstr(nome, 99);

               noecho();
               curs_set(0);


               classifica.aggiungiRisultato(nome, player.getPunteggio());
               classifica.salvaSuFile_v2();
               clear();
               refresh();
               //set_border();
               //stamp_screen();


          }

          else if ( selezione == 1 ) {

               classifica.stampaClassifica() ;

          }

          else {

               menu.mostraInfo() ;

          }

          menu.stampa();

          while (menu.leggiInput() != '\n') {
          }

          selezione = menu.getSelezione();

     }


     endwin(); //termina stdscr


    return 0;
}