//
// Created by andre on 07/09/2026.
//

#ifndef BOMBERMAN_MENU_H
#define BOMBERMAN_MENU_H
#include <curses.h>

class Menu {
protected:
    WINDOW* win ;
    int selezione ;
    const int altezza = 11 ;
    const int larghezza = 43 ;

public:
    Menu() ;

    void stampa() ;
    //stampa tutte le opzioni
    //evidenzia quella selezionata

    int leggiInput() ;

    void gestisciInput(char input) ;

    int getSelezione() const;
    //restituisce la selezione
};


#endif //BOMBERMAN_MENU_H