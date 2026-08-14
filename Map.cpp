#include "Map.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Map::Map(int height, int width, int start_Y, int start_X){
    rows = height;
    cols = width;

    win = newwin(height + 2, width + 2, start_Y, start_X);

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


void Map::stamp_map(const Personaggio& p, const Nemico nemici[], int numNemici, const Item items[], int numItems, const Bomba& b ){

    box(this->win, 0, 0);

    for(int i = 0; i < rows; i++){
        for(int j=0; j < cols; j++){
            char char_to_display = grid[i][j]; // Inizia con il carattere base della mappa

            // Priorità 4: Item (la più bassa tra gli oggetti dinamici)
            // Controlla se c'è un item attivo in questa posizione
            for(int k = 0; k < numItems; k++){
                if(items[k].isAttivo() && i == items[k].getY() && j == items[k].getX()){
                    char_to_display = items[k].getTipo(); // Stampa il tipo di item (es. 'B', 'T', 'D')
                    break; // Trovato un item, non serve controllare gli altri per questa cella
                }
            }

            // Priorità 3: Nemico (sovrascrive l'item se presente)
            // Controlla se c'è un nemico in questa posizione
            for(int k = 0; k < numNemici; k++){
                for(int k=0; k < numNemici; k++){
                    if(i == nemici[k].getY() && j == nemici[k].getX()){
                        char_to_display = 'N'; // 'N' per nemico (de gestire poi i vari tipi di nemici)
                        break; // Trovato un nemico, non serve controllare gli altri per questa cella
                    }
                }
            }

            // Priorità 2: Bomba (sovrascrive nemico e item se presente)
            if(b.innescata() && i == b.getY() && j == b.getX()){
                char_to_display = 'O'; // 'O' per bomba
            }

            // Priorità 1: Giocatore (la più alta, sovrascrive tutto)
            if(i == p.getY() && j == p.getX()){
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

