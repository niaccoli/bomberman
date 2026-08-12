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

/*
legenda:
top_left_angle = '╔'
top_right_angle = '╗'
bottom_left_angle = '╚'
bottom_right_angle = '╝'
top/bottom_border = '═'
left/right_border = '║'
destroyable_wall = ''
unbreakable_wall = ''
empty_space = ' ' 
bomb = ''
enemy = ''
player = ''
perk = ....
*/
/*
const char TOP_LEFT_ANGLE = 'A';
const char TOP_RIGHT_ANGLE = 'B';
const char BOTTOM_LEFT_ANGLE = 'C';
const char BOTTOM_RIGHT_ANGLE = 'D';
const char HORIZONTAL_BORDER = 'H';
const char VERTICAL_BORDER = 'V';
const char EMPTY = ' ';

void set_border(){
    screen[0][0] = TOP_LEFT_ANGLE;
    screen[0][width - 1] = TOP_RIGHT_ANGLE;
    screen[height - 1][0] = BOTTOM_LEFT_ANGLE;
    screen[height - 1][width - 1] = BOTTOM_RIGHT_ANGLE;
    for(int i = 1; i < width - 1; i++){
        screen[0][i] = HORIZONTAL_BORDER;
        screen[height - 1][i] = HORIZONTAL_BORDER;
    }
    for(int i = 1; i < height - 1; i++){
        screen[i][0] = VERTICAL_BORDER;
        screen[i][width - 1] = VERTICAL_BORDER;
    }
    //temp:
    for(int i = 1; i < height - 1; i++){
        for(int j = 1; j < width - 1; j++){
            screen[i][j] = EMPTY;
        }
    }
}

void check_character(int y, int x){
    if (screen[y][x] == TOP_LEFT_ANGLE)
        cout<<"╔";
    else if(screen[y][x] == TOP_RIGHT_ANGLE)
        cout<<"╗";
    else if (screen[y][x] == BOTTOM_LEFT_ANGLE)
        cout<<"╚";
    else if (screen[y][x] == BOTTOM_RIGHT_ANGLE)
        cout<<"╝";
    else if (screen[y][x] == HORIZONTAL_BORDER)
        cout<<"═";
    else if (screen[y][x] == VERTICAL_BORDER)
        cout<<"║";
    else if (screen[y][x] == EMPTY)
        cout<<" ";
    

}

void stamp_screen(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            check_character(i,j);
        }
        cout<<endl;
    }
}
*/

void menu(){
    
}


int main() {

    BidirectionalList levelList;

    //levelList.Create_Levels(); //TEST


    //inizializza lo schermo
    //setta la memoria e pulisce lo schermo (ncurses)
    initscr();

    int const start_y = 3;
    int const start_x = 5;

    //Puntatore alla finestra window
    WINDOW *win = newwin(height, width, start_y, start_x);

    //Aggiorna lo schermo per farlo matchare a ciò c he è presente in memoria
    refresh();

    //Crea un bordo attorno alla window
    box(win, 0, 0);
    wrefresh(win);

    // TEST
    //node* currentNode = levelList.getCurrent();
    //currentNode->map->stamp_map();
    //

    //Prende l'input dell'utente restituendo il valore int corrispondente al tasto premuto
    getch();

    //Muove il cursore alle coordinate specificate
    //move(y, x);

    //dealloca la memoria e termina ncurses
    endwin();







//Prima del game loop creiamo un solo giocatore e una sola lista bidirezionale dei livelli:
    //Giocatore player;
    //BidirectionalList levels;

/*Poi la lista contiene diversi nodi:
    levels
      |
      v
    [Level 1] <--> [Level 2] <--> [Level 3] <--> ...

e ogni Level mantiene tutto il proprio stato:
    Level
        │
        ├── Map
        ├── nemici_r[]
        ├── num_nemici_r
        ├── nemici_i[]
        ├── num_nemici_i
        ├── items[]
        ├── num_items
        ├── Bomba
        └── completato

COSA VIVE DOVE:
    MAIN
    │
    ├── Giocatore player
    │
    └── BidirectionalList levels
           │
           ├── node
           │    └── Level 1
           │          ├── Map
           │          ├── Nemici
           │          ├── Item
           │          └── Bomba
           │
           ├── node
           │    └── Level 2
           │          ├── Map
           │          ├── Nemici
           │          ├── Item
           │          └── Bomba
           │
           └── ...

La lista ha poi un current che identifica il livello in cui si trova attualmente il giocatore.

l'idea del main prima del loop sarebbe:

    1. Creo il giocatore

    2. Creo le mappe

    3. Creo i Level:
          Level 1 → Map 1, X nemici, X item, propria bomba
          Level 2 → Map 2, Y nemici, Y item, propria bomba
          Level 3 → Map 3, Z nemici, Z item, propria bomba

    4. Inserisco i Level nella lista bidirezionale

    5. current = primo livello

    6. INIZIA GAME LOOP

    prima di scrivere il loop: decidere esattamente chi deve creare i Level e i nodi della lista.
    terrei una struttura del genere:

        class BidirectionalList {
            private:
                node* head;
                node* current;

            public:
                BidirectionalList();

                void Create_Levels();

                void goToNext();
                void goToPrev();

                node* getCurrent();
        };

    Nel main poi avresti:

        int main() {

            Giocatore player;

            BidirectionalList levels;
            levels.Create_Levels();

            while (player.vivo()) {

                node* current = levels.getCurrent();

                // input
                // aggiornamento livello
                // collisioni
                // cambio livello
                // stampa
            }
        }



    funzioni.cpp lo userei per un altro scopo

    Il vostro funzioni.h attualmente contiene cose come:

    void muoviGiocatore(...);
    void piazzaBomba(...);
    void gestisciInput(...);
    Item generaItem(...);

    Queste sono funzioni relative alla logica del gioco, non alla struttura dati che contiene i livelli.

    SEPARAZIONE CONCETTUALE :
    BidirectionalList
        ↓
    gestisce la navigazione tra livelli

    Level
        ↓
    gestisce lo stato e la logica del singolo livello

    funzioni
        ↓
    eventuali operazioni generali del gioco

    main
        ↓
    coordina tutto


    gestisciInput cambierebbe un po'
    void gestisciInput(Giocatore& player,
                       Bomba& b,
                       Map& m,
                       char input);
    Ma se ora bomba e mappa appartengono al Level

    void gestisciInput(Giocatore& player,
                       BidirectionalList& levels,
                       char input);

    oppure, ancora meglio, tenere la funzione focalizzata sul livello corrente:
    void gestisciInput(Giocatore& player,
                       Level& level,
                       char input);

    e lasciare al main il cambio di livello.

    Per esempio concettualmente:
    node* current = levels.getCurrent();
    gestisciInput(player, *(current->level), input);

    Se il giocatore raggiunge l'uscita:
    levels.goToNext();

    Questo mantiene ben separate le responsabilità.

    BidirectionalList rappresenta la struttura che collega i livelli; Level rappresenta ciò che esiste dentro un livello.

    Una piccola cosa da correggere subito nella classe attuale: il vostro getCurrent() ha:
    node* BidirectionalList::getCurrent(){
        this->current;
    }
    ma manca il return


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

    return 0;
}


