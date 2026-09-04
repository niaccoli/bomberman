#include "Personaggio.hpp"

Personaggio::Personaggio(): vite(1), posizione{-1, -1 }{}

Personaggio::Personaggio(int vite, int x, int y): vite(vite), posizione{ x, y } {}

Personaggio::Personaggio(int vite, Posizione posizione): vite(vite), posizione(posizione) { }


void Personaggio::setX(int x) {
    this -> posizione.x = x;
}

void Personaggio::setY(int y) {
    this -> posizione.y = y;
}

void Personaggio::setPosizione(Posizione posizione) {
    this -> posizione = posizione ;
}



int Personaggio::getX () const {
    return posizione.x ;
}

int Personaggio::getY () const {
    return posizione.y ;
}

Posizione Personaggio::getPosizione() const {
    return this -> posizione ;
}



void Personaggio::muovi(int newx, int newy) {
    setX(newx);
    setY(newy);
}

void Personaggio::muovi(Posizione newp) {
    posizione = newp ;
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

void Personaggio::diminuisciVita(int danno) {
    this -> vite -= danno ;
}


bool Personaggio::vivo () const{
    return (vite > 0);
}


int Personaggio::getVite() const {
    return vite;
}




