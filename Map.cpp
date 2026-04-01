#include "Map.hpp"

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

void Map::initialize_map(int levelID){

    switch(levelID){
        case 1:

            break;
        case 2:
    }
}

void Map::stamp_map(){
    werase(win); //Pulisce la finestra (probabilemnte eliminabile gestendo ogni finestra in modo separato per ogni sezione del gioco (es menu, livello, classifica, etc,))
    box(win, 0, 0);

    for(int i = 1; i < rows - 1; i++){
        for(int j = 1; j < cols - 1; j++){
            wmove(win, i, j);
            addch(grid[i][j]);
        }
    }
    wrefresh(win);
};