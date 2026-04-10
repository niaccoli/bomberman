#include "Map.hpp"
#include <fstream>

using namespace std;

Map::Map(int height, int width, int start_Y, int start_X){
    rows = height;
    cols = width;

    win = newwin(height, width, start_Y, start_X);

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


void Map::stamp_map(){
    werase(win); //Pulisce la finestra (probabilmente eliminabile gestendo ogni finestra in modo separato per ogni sezione del gioco (es menu, livello, classifica, etc,))
    box(win, 0, 0);

    for(int i = 1; i < rows - 1; i++){
        for(int j = 1; j < cols - 1; j++){
            wmove(win, i, j);
            addch(grid[i][j]);
        }
    }
    wrefresh(win);
};