#include "Personaggio.hpp"

Personaggio::Personaggio(): vite(1), x(-1), y(-1){}

Personaggio::Personaggio(int vite, int x, int y): vite(vite), x(x), y(y){}

void Personaggio::setX(int x) {
    this -> x = x;
}

void Personaggio::setY(int y) {
    this -> y = y;
}

int Personaggio::getX () const {
    return x;
}

int Personaggio::getY () const {
    return y;
}


void Personaggio::muovi(int newx, int newy) {
    setX(newx);
    setY(newy);
}

void Personaggio::setVite(int vite) {
    this->vite = vite;
}

void Personaggio::aumentaVita() {
    this -> vite += 1;
}

void Personaggio::diminuisciVita() {
    this -> vite -= 1;
}

bool Personaggio::vivo () const{
    return (vite > 0);
}


int Personaggio::getVite() const {
    return vite;
}




