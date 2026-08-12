#include <iostream>
#include <cstring>
//#include <ncurses.h>
#include <curses.h>
#include "Map.hpp"
#include "BidirectionalList.hpp"

using namespace std;



//dimensioni matrice: 25x70, con due righe e due colonne in più per i bordi.
const int width = 72;
const int height = 27;
char screen[height][width];


void menu(){
    
}



int main() {

    

    //inizializza lo schermo
    //setta la memoria e pulisce lo schermo (ncurses)
    initscr();
    noecho(); //Non mostra il carattere della tastiera in input
    curs_set(0); //Nasconde il cursore

    BidirectionalList levelList;

    levelList.Create_Levels();

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
    Personaggio p;

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
    endwin();

    //char input ;
    //Giocatore player ;
    //Bomba b ; //crea un oggetto bomba posizionato fuori dalla mappa e non attiva
    //Map m ;

    //LOOP:
    /*
     *
    //cin >> input ;
     *INPUT:
    gestisciInput(player, bomba, mappa, input) ;
    //precondizione: l'utente inserisce l'input da tastiera
    //postcondizione: se input ('W''A''S''D') e posizione mossa valida la posizione del giocatore viene aggiornata, altrimenti
    //mantiene la stessa posizione. Se input 'X' e non e' gia presente una bomba innescata,
    //viene posizionata una bomba nella stessa posizione del giocatore.
    //Se input non valido non viene effettuata alcuna azione.



    MUOVI NEMICI:
    NemicoRandom : Muovi() serve funzione posizione valida


    CONTROLLA COLLISIONI:
    void controllaCollisioni(Giocatore& g, Nemico& n[], Mappa& m, Bomba& b, Item i);


    STAMPA:
    guarda l esempio mandato su whatsapp
    ti ho scritto anche l esempio in map.cpp
    *
    *
    *Aggiorna bomba

    */






    //set_border();
    //stamp_screen();

    endwin();


    return 0;
}


