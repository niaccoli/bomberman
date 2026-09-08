#include "Menu.hpp"
#include <curses.h>

Menu::Menu() {
    win = newwin(altezza, larghezza, 1, 1);
    wtimeout(win, -1);

    selezione = 0 ;

}


void Menu::stampa() {

    const char* opzioni[] = {
        "Nuova partita",
        "Classifica",
        "Info",
        "Uscita"
    };

    const int NUM_OPZIONI = 4;

    werase(win);

    for (int i = 0; i < NUM_OPZIONI; i++) {

        int y = i * 2;
        int x = 0;

        if (i == selezione)
            wattron(win, A_BOLD);

        mvwprintw(win, y, x, "%s", opzioni[i]);

        if (i == selezione)
            wattroff(win, A_BOLD);
    }

    wrefresh(win);
}

int Menu::leggiInput() {

    wtimeout(win, -1);

    int input = wgetch(win);

    if (input != '\n')
        gestisciInput(input);

    return input;
}

void Menu::gestisciInput(char input) {

    if (input == 'w' || input == 'W') {

        if (selezione == 0)
            selezione = 3;
        else
            selezione--;
    }

    else if (input == 's' || input == 'S') {

        if (selezione == 3)
            selezione = 0;
        else
            selezione++;
    }

    stampa() ;
}


int Menu::getSelezione() const {
    return selezione;
}

void Menu::mostraInfo( ) const{

    clear();

    noecho();
    curs_set(0);
    timeout(-1);


    mvprintw(1, 1, "INFO DI GIOCO");


    // COMANDI
    mvprintw(3, 1, "Comandi:");

    mvprintw(4, 3, "W -> movimento verso l'alto");
    mvprintw(5, 3, "S -> movimento verso il basso");
    mvprintw(6, 3, "A -> movimento verso sinistra");
    mvprintw(7, 3, "D -> movimento verso destra");
    mvprintw(8, 3, "X -> piazza bomba");


    // NEMICI
    mvprintw(10, 1, "Tipologie di nemici:");

    mvprintw(11, 3, "Inseguitore -> simbolo: $  -> 200 punti");

    mvprintw(12, 3, "Tank (2 vite) -> simbolo: ");
    move(12, 31);
    addch(ACS_DIAMOND);
    printw("  -> 150 punti");

    mvprintw(13, 3, "Random -> simbolo: Ö  -> 100 punti");


    // ITEM
    mvprintw(15, 1, "Tipologie di item:");

    mvprintw(16, 3, "D -> Aumento danno bomba");
    mvprintw(17, 3, "R -> Aumento raggio bomba");
    mvprintw(18, 3, "T -> Riduzione timer esplosione");
    mvprintw(19, 3, "I -> Invulnerabilita ");
    mvprintw(20, 3, "V -> +1 vita");


    // PUNTEGGIO
    mvprintw(22, 1, "Punteggio:");
    mvprintw(23, 3, "Se la partita viene vinta, al punteggio viene sommato");
    mvprintw(24, 3, "il tempo rimasto in secondi.");


    mvprintw(26, 1, "Premi INVIO per tornare al menu");

    refresh();


    int input = getch();

    while (input != '\n')
        input = getch();


    clear();
    refresh();
}