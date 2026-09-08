//
// Created by andre on 07/09/2026.
//

#include "Menu.h"
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