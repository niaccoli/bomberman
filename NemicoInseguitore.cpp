#include "NemicoInseguitore.h"
#include "Map.hpp"
#include "Giocatore.h"

NemicoInseguitore::NemicoInseguitore(): Personaggio(){}

void NemicoInseguitore::muovi(Map& m, Giocatore& player) {

    int dx = 0;
    int dy = 0;

    if (player.getX() > getX())
        dx = 1;
    else if (player.getX() < getX())
        dx = -1;

    int newX = getX() + dx;
    int newY = getY();

    /*if (mossaValida(m, newX, newY)) {
        muovi(newX, newY);
        return;
    }*/


    if (player.getY() > getY())
        dy = 1;
    else if (player.getY() < getY())
        dy = -1;

    newX = getX();
    newY = getY() + dy;

    /*if (mossaValida(m, newX, newY)) {
        muovi(newX, newY);
    }*/
}

