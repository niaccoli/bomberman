#include "Mappa.hpp"
#include "Nemico.h"
#include <fstream>
#include <iostream>
#include <random>
#include <cmath> //Usato per funzione abs() (Valore assoluto)
#include "Timer.h"
#include "funzioni.h"
#include "Posizione.h"

using namespace std;

Mappa::Mappa(int height, int width){
    rows = height;
    cols = width;


    //gli ultimi 2 parametri provvisori (Devo controllare se sono giusti)
    win = newwin(height + 2, width + 2, 1, 1);

    //allocazione dinamica della matrice
    grid = new char*[rows];
    for(int i = 0; i < rows; i++){
        grid[i] = new char[cols];
    }
};

Mappa::~Mappa() {
    // 1. Libera le colonne per ogni riga
    for (int i = 0; i < rows; i++) {
        delete[] grid[i]; 
    }
    // 2. Libera l'array delle righe
    delete[] grid;    

    // 3. Libera la memoria della finestra ncurses
    if (win != nullptr) {
        delwin(win);
    }
}

void Mappa::inizializzaMappa(int levelID){
    string fileName;

    switch(levelID) {
        case 1: fileName = "level1.txt"; break;
        case 2: fileName = "level2.txt"; break;
        case 3: fileName = "level3.txt"; break;
        case 4: fileName = "level4.txt"; break;
        case 5: fileName = "level5.txt"; break;
        default: return; // Livello non valido
    }

    ifstream file(fileName);
    if (!file.is_open()) return;

    char ch;
    int r = 0, c = 0;
    while (file.get(ch) && r < rows) {
        if (ch == '\n') {
            r++;
            c = 0;
        } else if (c < cols) {
            if(ch == '@'){
                entry.x = c;
                entry.y = r;
            }
            else if(ch == 'U'){
                exit.x = c;
                exit.y = r;
            }
            grid[r][c] = ch;
            c++;
        }
    }
    file.close();
        
}

//Prende in input due coordinate e restituiisce TRUE se è superficie calpestabile (spazio vuoto o Item)
bool Mappa::mossavalida(int x, int y){

    //Controllo limiti mappa (probabilemtne non serve ma è per sicurezza)
    if (x >= cols || y >= rows || x < 0 || y < 0)
        return false;
    if (grid[y][x] == ' ' ||  grid[y][x] == 'I') //da capire se il player può andare nella stessa cella di un nemico o meno
        //Andrea: si il giocatore puo' può andare nella stessa cella di un nemico perche poi se la cella e' la stessa
            //quando si fa il controllo collisioni il giocatore perde la vita
                //pero' un nemico non dovrebbe poter andare nella cella occupata da un altro nemico
        return true;
    
    return false;
}

// 1. Versione standard (chiamata quando non c'è esplosione)
void Mappa::stampaMappa(const Giocatore& p, const Nemico nemici[], int numNemici, 
                    const Item items[], int numItems, const Bomba& b, int timer_gioco) {
    // Chiama direttamente la versione completa passando NULL e 0
    this->stampaMappa(p, nemici, numNemici, items, numItems, b, NULL, 0, timer_gioco);
}

bool cambia_colore_bomba = false;
Timer cambia_colore(1);

Posizione mappa_schermo;


void Mappa::stampaMappa(const Giocatore& p, const Nemico nemici[], int numNemici, const Item items[], int numItems, const Bomba& b, Posizione celle_esplosione[], int num_celle_esplosione, int timer_gioco){

    int larghezza_stats = 30; // Larghezza stimata per le statistiche a destra
    int total_w = this->cols + 2 + larghezza_stats;
    int total_h = this->rows + 2;

    int start_y = (LINES - rows) / 2;
    int start_x = (COLS - cols) / 2;

    // Controllo di sicurezza per evitare coordinate negative se il terminale è piccolo:
    if (start_y < 0) start_y = 0;
    if (start_x < 0) start_x = 0;

    // Crea la finestra della mappa centrata (altezza, larghezza, start_y, start_x)
    this->win = newwin(this->rows + 2, this->cols + 2, start_y, start_x);

    mappa_schermo.x = start_x + cols;
    mappa_schermo.y = start_y;
    

    werase(this->win);
    box(this->win, 0, 0);

    //GESTIONE TIMER
    // Gestione lampeggio bomba
    cambia_colore.diminuisci(1);
    if(cambia_colore.scaduto()){                   
        cambia_colore_bomba = !cambia_colore_bomba;
        cambia_colore.attivaTimer(5); // Cambia colore ogni 5 frame
    }
    

    for(int i = 0; i < rows; i++){
        for(int j=0; j < cols; j++){
            char carattere_da_mostrare = grid[i][j]; // Inizia con il carattere base della mappa


            //Priorità piu bassa, stampa entrata ed uscita come spazio vuoto
            if(carattere_da_mostrare == '@' || carattere_da_mostrare == 'U'){
                carattere_da_mostrare = ' ';

                // TRUCCO: Cancelliamo il pezzo di bordo di ncurses!
                if (j == 0)             // Bordo Sinistro
                    mvwaddch(this->win, i + 1, 0, ' ');
                else if (j == cols - 1) // Bordo Destro
                    mvwaddch(this->win, i + 1, cols + 1, ' ');
                else if (i == 0)        // Bordo Superiore
                    mvwaddch(this->win, 0, j + 1, ' ');
                else if (i == rows - 1) // Bordo Inferiore
                    mvwaddch(this->win, rows + 1, j + 1, ' ');
            }


            // Priorità 5: Item (la più bassa tra gli oggetti dinamici)
            // Controlla se c'è un item attivo in questa posizione
            for(int k = 0; k < numItems; k++){
                if(items[k].isAttivo() && i == items[k].getY() && j == items[k].getX()){
                    carattere_da_mostrare = items[k].getTipo(); // Stampa il tipo di item (es. 'B', 'T', 'D')
                    break; // Trovato un item, non serve controllare gli altri per questa cella
                }
            }

            // Priorità 4: Nemico (sovrascrive l'item se presente)
            // Controlla se c'è un nemico in questa posizione
            for(int k = 0; k < numNemici; k++){
                if(i == nemici[k].getY() && j == nemici[k].getX()){
                    if(!nemici[k].vivo())
                        carattere_da_mostrare = ' ';
                    else{
                        if(nemici[k].getTipo() == 'I')
                            carattere_da_mostrare = 'A'; // 'A' per nemico inseguitore
                        else if(nemici[k].getTipo() == 'T')
                            carattere_da_mostrare = 'B'; // 'B' per nemico Tank
                        else
                            carattere_da_mostrare = 'C'; // 'C' per nemico Random
                    }
                    
                    break; // Trovato un nemico, non serve controllare gli altri per questa cella
                }
            }

            // Priorità 3: Bomba (sovrascrive nemico e item se presente)
            if(b.innescata() && i == b.getY() && j == b.getX()){
                carattere_da_mostrare = 'O'; // 'O' per bomba
            }

            for (int k = 0; k < num_celle_esplosione; k++) {
                        if (i == celle_esplosione[k].y && j == celle_esplosione[k].x) {
                            carattere_da_mostrare = 'E';
                            break;
                        }
                    }

            // Priorità 1: Giocatore (la più alta, sovrascrive tutto)
            if(p.vivo() && i == p.getY() && j == p.getX()){
                carattere_da_mostrare = 'P'; // 'P' per giocatore
            }

            // 2. RENDERIZZAZIONE GRAFICA MODERNA
            // Stampiamo con OFFSET di +1 per salvare i bordi della finestra
            if (carattere_da_mostrare == '#')
                mvwaddstr(this->win, i + 1, j + 1, "█");
            else if(carattere_da_mostrare == 'X')
                mvwaddstr(this->win, i + 1, j + 1, "▒");
            else if(carattere_da_mostrare == 'P'){
                wattron(this->win, COLOR_PAIR(1) | A_BOLD);
                mvwaddstr(this->win, i + 1, j + 1, "@");
                wattroff(this->win, COLOR_PAIR(1) | A_BOLD);
            }
            else if(carattere_da_mostrare == 'A'){
                wattron(this->win, COLOR_PAIR(2) | A_BOLD);
                mvwaddstr(this->win, i + 1, j + 1, "$");
                wattroff(this->win, COLOR_PAIR(2) | A_BOLD);
            }
            else if(carattere_da_mostrare == 'B'){
                wattron(this->win, COLOR_PAIR(2) | A_BOLD);
                mvwaddch(this->win, i + 1, j + 1, ACS_DIAMOND);
                wattroff(this->win, COLOR_PAIR(2) | A_BOLD);
            }
            else if(carattere_da_mostrare == 'C'){
                wattron(this->win, COLOR_PAIR(2) | A_BOLD);
                mvwaddstr(this->win, i + 1, j + 1, "Ö");
                wattroff(this->win, COLOR_PAIR(2) | A_BOLD);
            }
            else if(carattere_da_mostrare == 'O'){

                if(cambia_colore_bomba == true){
                    wattron(this->win, COLOR_PAIR(3) | A_BOLD);
                    mvwaddstr(this->win, i + 1, j + 1, "¤");
                    wattroff(this->win, COLOR_PAIR(3) | A_BOLD);
                }
                else{
                    wattron(this->win, COLOR_PAIR(2) | A_BOLD);
                    mvwaddstr(this->win, i + 1, j + 1, "¤");
                    wattroff(this->win, COLOR_PAIR(2) | A_BOLD);
                }
                
            }
            else if(carattere_da_mostrare == 'E'){
                wattron(this->win, COLOR_PAIR(6) | A_BOLD);
                mvwaddstr(this->win, i + 1, j + 1, "█");
                wattroff(this->win, COLOR_PAIR(6) | A_BOLD);
            }
            else if(carattere_da_mostrare == ' '){
                mvwaddch(this->win, i + 1, j + 1, carattere_da_mostrare);
            }       
            else {
                //ITEM
                wattron(this->win, COLOR_PAIR(4) | A_BOLD);
                mvwaddch(this->win, i + 1, j + 1, carattere_da_mostrare);
                wattroff(this->win, COLOR_PAIR(4) | A_BOLD);
            }

        }
    }

    StampaInfo(p, b, timer_gioco, mappa_schermo);
    

    //Aggiorna la finestra
    wrefresh(this->win);
}




void Mappa::distruggiMuro() {
    //da scrivere
}


bool Mappa::isCamminabile (Posizione posizione ) {

    if (posizione.y < 0 || posizione.y >= rows || posizione.x < 0 || posizione.x >= cols) {
        return false;
    }

    char current_cell = grid[posizione.y][posizione.x];

    if( current_cell == '#' || current_cell == 'X' || current_cell == 'O')
        return false;
    return true;
}

bool Mappa::isCamminabile (int x, int y ) {
    Posizione temp = {x , y} ;
    return isCamminabile(temp) ;
}


Posizione Mappa::posizioneCamminabileRandom( ) {
    //utilizzo static per iniziallizarli solo una volta
    static random_device rnd;

    //Motore pseudocasuale con algoritmo Marsenne Twister
    static mt19937 gen(rnd());

    //Escludo la prima e ultima riga/colonna sapendo che, essendo i bordi della mappa non sono mai calpestabili
    uniform_int_distribution<int> random_row(1, rows - 2);
    uniform_int_distribution<int> random_col(1, cols - 2);

    Posizione rnd_position;

    do{       
        rnd_position.x = random_col(gen);
        rnd_position.y = random_row(gen);

    }while(!isCamminabile(rnd_position));

    return rnd_position;
}


void Mappa::distruggiMuro(Posizione posizione) {
    if(isDistruttibile(posizione))
        grid[posizione.y][posizione.x] = ' ';
}


bool Mappa::isDistruttibile( Posizione posizione ) {
    if(grid[posizione.y][posizione.x] == 'X')
        return true;
    return false;
}

bool Mappa::isMuroIndistruttibile ( Posizione posizione ) {
    if(grid[posizione.y][posizione.x] == '#')
        return true;
    return false;
}


int Mappa::getRighe(){
    return rows;
}


int Mappa::getCols(){
    return cols;
}


bool Mappa::cellaSenzaMuro(int x, int y){
    if(grid[y][x] == 'X' || grid[y][x] == '#')
        return false;
    return true;
}

Posizione Mappa::getEntrata(){
    Posizione posizione_entrata;

    posizione_entrata.x = entry.x;
    posizione_entrata.y = entry.y;

    return posizione_entrata;
}

Posizione Mappa::getUscita(){
    Posizione posizione_uscita;

    posizione_uscita.x = exit.x;
    posizione_uscita.y = exit.y;

    return posizione_uscita;
}

bool Mappa::isEntrata(Posizione posizione){
    if(posizione.x == entry.x && posizione.y == entry.y)
        return true;
    return false;
}

bool Mappa::isUscita(Posizione posizione){
    if(posizione.x == exit.x && posizione.y == exit.y)
        return true;
    return false;
}

bool Mappa::isVicinoEntrata(Posizione posizione){
    if(posizione.x < entry.x + 4 && posizione.y <= entry.y + 2 && posizione.y > entry.y - 2)
        return true;
    return false;
}

bool Mappa::isCircondataDaMuri(Posizione p){
    if(grid[p.y + 1][p.x] != '#' && grid[p.y + 1][p.x] != 'X'){
        return true;
    }
    else if(grid[p.y - 1][p.x] != '#' && grid[p.y + 1][p.x] != 'X'){
        return true;
    }
    else if(grid[p.y + 1][p.x + 1] != '#' && grid[p.y + 1][p.x] != 'X'){
        return true;
    }
    else if(grid[p.y + 1][p.x - 1] != '#' && grid[p.y + 1][p.x] != 'X'){
        return true;
    }
    else
        return false;

}

char Mappa::getCell(Posizione posizione){
    return grid[posizione.y][posizione.x];
}