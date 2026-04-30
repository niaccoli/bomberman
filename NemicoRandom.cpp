#include "NemicoRandom.h"
#include "Map.hpp"
#include <cstdlib>


NemicoRandom::NemicoRandom(): Personaggio(){}

void NemicoRandom::muovi(Map &m) {
    int dir = rand() % 4;

    int dx = 0;
    int dy = 0;

    if (dir == 0) dy = -1; // W
    else if (dir == 1) dy = 1; // A
    else if (dir == 2) dx = -1; // S
    else if (dir == 3) dx = 1; // D

    int newX = getX() + dx;
    int newY = getY() + dy;

    //if (mossaValida(m, newX, newY)) {
        setX(newX);
        setY(newY);
}
