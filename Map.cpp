#include "Map.hpp"
#include "Nemico.h"
#include <fstream>
#include <iostream>
#include <random>
#include <cmath> //Usato per funzione abs() (Valore assoluto)

using namespace std;

Map::Map(int height, int width){
    rows = height;
    cols = width;


    //gli ultimi 2 parametri provvisori (Devo controllare se sono giusti)
    win = newwin(height + 2, width + 2, entry.x, entry.y);

    //allocazione dinamica della matrice
    grid = new char*[rows];
    for(int i = 0; i < rows; i++){
        grid[i] = new char[cols];
    }
};

void Map::Initialize_Map(int levelID){
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
bool Map::mossavalida(int x, int y){

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
void Map::stamp_map(const Personaggio& p, const Nemico nemici[], int numNemici, 
                    const Item items[], int numItems, const Bomba& b) {
    // Chiama direttamente la versione completa passando NULL e 0
    this->stamp_map(p, nemici, numNemici, items, numItems, b, NULL, 0);
}


void Map::stamp_map(const Personaggio& p, const Nemico nemici[], int numNemici, const Item items[], int numItems, const Bomba& b, Posizione celle_esplosione[], int num_celle_esplosione){

    box(this->win, 0, 0);

    for(int i = 0; i < rows; i++){
        for(int j=0; j < cols; j++){
            char char_to_display = grid[i][j]; // Inizia con il carattere base della mappa


            //Priorità piu bassa, stampa entrata ed uscita come spazio vuoto
            if(char_to_display == '@' || char_to_display == 'U'){
                char_to_display = ' ';
            }


            // Priorità 5: Item (la più bassa tra gli oggetti dinamici)
            // Controlla se c'è un item attivo in questa posizione
            for(int k = 0; k < numItems; k++){
                if(items[k].isAttivo() && i == items[k].getY() && j == items[k].getX()){
                    char_to_display = items[k].getTipo(); // Stampa il tipo di item (es. 'B', 'T', 'D')
                    break; // Trovato un item, non serve controllare gli altri per questa cella
                }
            }

            // Priorità 4: Nemico (sovrascrive l'item se presente)
            // Controlla se c'è un nemico in questa posizione
            for(int k = 0; k < numNemici; k++){
                if(i == nemici[k].getY() && j == nemici[k].getX()){
                    char_to_display = 'N'; // 'N' per nemico (de gestire poi i vari tipi di nemici)
                    break; // Trovato un nemico, non serve controllare gli altri per questa cella
                }
            }

            // Priorità 3: Bomba (sovrascrive nemico e item se presente)
            if(b.innescata() && i == b.getY() && j == b.getX()){
                char_to_display = 'O'; // 'O' per bomba
            }

            //Priorità 2: Esplosione bomba
            //Visualizzazione esplosione bomba (True da sostituire con meotodo per capire se la boma è esplosa)
            if(true){
                for (int k = 0; k < num_celle_esplosione; k++) {
                    if (i == celle_esplosione[k].y && j == celle_esplosione[k].x) {
                        char_to_display = 'E';
                        break;
                    }
                }
            }

            // Priorità 1: Giocatore (la più alta, sovrascrive tutto)
            if(p.vivo() && i == p.getY() && j == p.getX()){
                char_to_display = 'P'; // 'P' per giocatore
            }

            // 2. RENDERIZZAZIONE GRAFICA MODERNA
            // Stampiamo con OFFSET di +1 per salvare i bordi della finestra
            if (char_to_display == '#') {
                // MURO INDISTRUTTIBILE: Blocco Unicode pieno (senza fessure!)
                mvwaddstr(this->win, i + 1, j + 1, "█"); 
            } 
            else if (char_to_display == 'X') {
                // MURO DISTRUTTIBILE: Blocco sfumato
                mvwaddstr(this->win, i + 1, j + 1, "▒"); 
            }
            else {
                // Per tutti gli altri caratteri normali ('P', 'N', ' ') usiamo mvwaddch
                mvwaddch(this->win, i + 1, j + 1, char_to_display);
            }
        }
    }

    //Aggiorna la finestra
    wrefresh(this->win);
}




void Map::breakWall() {
    //da scrivere
}


bool Map::isWalkable (Posizione posizione ) {
    char current_cell = grid[posizione.y][posizione.x];

    if( current_cell == '#' || current_cell == 'X')
        return false;
    return true;
}


Posizione Map::walkableRandomPosition( ) {
    //utilizzo static per iniziallizarli solo una volta
    static random_device rnd;

    //Motore pseudocasuale con algoritmo Marsenne Twister
    static mt19937 gen(rnd());

    //Escludo la prima e ultima riga/colonna sapendo che, essendo i bordi della mappa non sono mai calpestabili
    uniform_int_distribution<int> random_row(1, rows - 1);
    uniform_int_distribution<int> random_col(1, cols - 1);

    Posizione rnd_position;

    do{       
        rnd_position.x = random_col(gen);
        rnd_position.y = random_row(gen);

    }while(!isWalkable(rnd_position));

    return rnd_position;
}


void Map::breakWall(Posizione posizione) {
    if(isBreakable(posizione))
        grid[posizione.y][posizione.x] = ' ';
}


bool Map::isBreakable( Posizione posizione ) {
    if(grid[posizione.y][posizione.x] == 'X')
        return true;
    return false;
}

bool Map::isUnbreakableWall ( Posizione posizione ) {
    if(grid[posizione.y][posizione.x] == '#')
        return true;
    return false;
}


int Map::getRows(){
    return rows;
}


int Map::getCols(){
    return cols;
}


bool Map::cell_without_wall(int x, int y){
    if(grid[y][x] == 'X' || grid[y][x] == '#')
        return false;
    return true;
}

Posizione Map::getEntry(){
    Posizione entry_position;

    entry_position.x = entry.x;
    entry_position.y = entry.y;

    return entry_position;
}

Posizione Map::getExit(){
    Posizione exit_position;

    exit_position.x = exit.x;
    exit_position.y = exit.y;

    return exit_position;
}

bool Map::isEntry(Posizione position){
    if(position.x == entry.x && position.y == entry.y)
        return true;
    return false;
}

bool Map::isExit(Posizione position){
    if(position.x == exit.x && position.y == exit.y)
        return true;
    return false;
}

bool Map::isNearEntry(Posizione position){
    if(position.x < entry.x + 4 && position.y <= entry.y + 2 && position.y > entry.y - 2)
        return true;
    return false;
}

