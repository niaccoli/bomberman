#include <iostream>
#include <cstring>

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


int main() {

    set_border();
    stamp_screen();

    return 0;
}


