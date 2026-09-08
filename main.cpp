#include <iostream>
#include <cstring>
//#include <ncurses.h>
#include <curses.h>
#include "Mappa.hpp"
#include "ListaBidirezionale.hpp"
#include "funzioni.hpp"
#include "Timer.hpp"
#include "Classifica.hpp"
#include "Menu.hpp"
#include <cstdlib>

using namespace std;



int main() {


     #ifdef _WIN32
          // Su Windows con PDCurses non è necessario impostare TERM
     #else
          setenv("TERM", "xterm-256color", 1);
     #endif


     //INIZIALIZZAZIONE CURSES
     setlocale(LC_ALL, "");
     initscr();
     noecho();
     curs_set(0);


     // Caricamento della classifica e creazione del menu principale.
     Classifica classifica ;
     classifica.caricaDaFile() ;
     Menu menu ;

     timeout(-1) ;
     menu.stampa() ;


     while (menu.leggiInput() != '\n') {
     }

     int selezione = menu.getSelezione();

     // Il programma continua finché l'utente non seleziona "Uscita".
     while ( selezione != 3 ) {
          if ( selezione == 0) {

               // Input non bloccante durante il game loop.
               timeout(0);

               clear() ;
               refresh();


               // Configurazione dei colori utilizzati durante la partita.
               if (has_colors()) {
                    start_color();
                    use_default_colors();


                    init_pair(1, COLOR_CYAN,    -1); // Giocatore
                    init_pair(2, COLOR_RED,     -1); // Nemici / Bomba
                    init_pair(3, COLOR_YELLOW,  -1); // Bomba
                    init_pair(4, COLOR_GREEN,   -1); // Item / Valuta
                    init_pair(5, COLOR_WHITE,   -1); // Muri indistruttibili
                    init_pair(6, COLOR_RED,  COLOR_RED);   // Esplosione
               }

               ListaBidirezionale levelList;
               levelList.CreaLivelli();


               Giocatore player(3, 1, 1);
               posizionaGiocatoreStart(player, levelList);

               // Parametri temporali della partita.
               const int INTERVALLO_CICLO_MS = 100;
               const int TEMPO_AGGIORNAMENTO_NEMICI_MS = 1000 ;
               const int DURATA_PARTITA_MINUTI = 10 ;

     Timer timerGioco(DURATA_PARTITA_MINUTI * 60 * 1000) ;
     int timer_gioco = timerGioco.getTimer();
     Timer timerNemici (TEMPO_AGGIORNAMENTO_NEMICI_MS) ;

     //3 PRIMA STAMPA
     levelList.getCurrent()->level->stampaMappa(player, timer_gioco);

               // Game loop.
               while ( player.vivo() && !timerGioco.scaduto( )) {


                    char temp;
                    char input = ERR;

                    //svuota la coda di input tenendo solo l'ultimo tasto premuto
                    while ((temp = getch()) != ERR)
                         input = temp;

                    if (input != ERR)
                         gestisciInput(player, levelList, input);

                    // Gestione del passaggio tra livelli.
                    controllaPassaggioLivelli( player, levelList ) ;

                    // Aggiornamento degli effetti temporanei.
                    player.aggiornaInvulnerabilita( INTERVALLO_CICLO_MS ) ;
                    levelList.updateBoostBombe(INTERVALLO_CICLO_MS ) ;


                    bool colpito = false;

                    // I nemici vengono aggiornati a intervalli più lunghi rispetto al game loop.
                    if ( timerNemici.scaduto()) {
                         levelList.muoviNemici( player ) ;
                         timerNemici.attivaTimer(TEMPO_AGGIORNAMENTO_NEMICI_MS ) ;
                    }

                    // Controllo delle collisioni con nemici ed esplosioni.
                    colpito = levelList.collisioniGiocatoreNemici(player ) ;

                    if ( !colpito )
                         colpito = levelList.aggiornaBomba( player, INTERVALLO_CICLO_MS ) ;

                    // Raccolta e applicazione degli item.
                    if (!colpito) {
                         char tipo = levelList.getCurrent()->level->raccoltaItem(player);

                         if (tipo != ' ')
                              levelList.applicaEffettoItem(player, tipo);
                    }

          // Aggiornamento della visualizzazione.
          timer_gioco = timerGioco.getTimer();
          levelList.getCurrent() -> level -> stampaMappa( player, timer_gioco );

          // Se il giocatore subisce danno viene riposizionato,
          // a meno che abbia esaurito le vite.
          if ( colpito ) {
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


                    // Aggiornamento dei timer.
                    timerNemici.diminuisci(INTERVALLO_CICLO_MS) ;
                    timerGioco.diminuisci(INTERVALLO_CICLO_MS) ;

                    // Mantiene costante la frequenza del game loop.
                    napms(INTERVALLO_CICLO_MS) ;
               }


               // Gestione della fine della partita.
               char nome[100];

               timeout(-1);

               clear();

               if (player.vivo() && !timerGioco.scaduto()) {
                    // Il tempo residuo viene aggiunto al punteggio in caso di vittoria.
                    player.aumentaPunteggio(timerGioco.getTimer() / 1000);
                    mvprintw(1, 1, "HAI VINTO!");
               }
               else if (player.vivo() && timerGioco.scaduto())
                    mvprintw(1, 1, "TEMPO SCADUTO! GAME OVER");
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

               // Salvataggio del risultato nella classifica.
               classifica.aggiungiRisultato(nome, player.getPunteggio());
               classifica.salvaSuFile();

               clear();
               refresh();


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

     // Chiusura di curses prima della terminazione del programma.
     endwin();


    return 0;
}