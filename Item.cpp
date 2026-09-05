#include "Item.h"
#include <cstdlib>

Item::Item(): posizione{ -1, -1 }, tipo(' '), /*durata(0),*/ attivo(false){}

Item::Item(int x, int y, char tipo, /*int durata,*/ bool attivo): posizione{ x, y }, tipo(tipo), /*durata(durata),*/ attivo(attivo){}

void Item::setX(int x) {
    this->posizione.x = x;
}

void Item::setY(int y) {
    this->posizione.y = y;
}

void Item::setPosizione(Posizione posizione) {
    this -> posizione = posizione ;
}

void Item::setPosizione(int x, int y) {
    this -> posizione.x = x ;
    this -> posizione.y = y ;
}


int Item::getX() const {
    return this -> posizione.x;
}

int Item::getY() const {
    return this -> posizione.y;
}

Posizione Item::getPosizione( ) const {
    return this -> posizione ;
}



void Item::setTipo(char tipo) {
    if ( tipo == 'D' || tipo == 'R' || tipo == 'T' || tipo == 'I' || tipo == 'V')
        this -> tipo = tipo;
    else
        this -> tipo = ' ' ;
}


void Item::setTipoRandom_v2() {
    int i = rand() % 100 ;
    if (i >= 0 && i < 30) {
        setTipo('D') ;
    }
    else if (i >= 30 && i < 60) {
        setTipo('R') ;
    }
    else if (i >= 60 && i < 90) {
        setTipo('T') ;
    }
    else if (i >= 90 && i < 95) {
        setTipo('I') ;
    }
    else {
        setTipo('V') ;
    }
}

char Item::getTipo() const {
    return this -> tipo;
}

/*void Item::setDurata(int tempo) {
    this -> durata = tempo;
}*/

/*int Item::getDurata() const {
    return this -> durata;
}*/

bool Item::isAttivo() const{
    return this -> attivo;
}

void Item::raccogli() {
    disattiva();
}

void Item::disattiva() {
    attivo = false;
    //setDurata(0);
}

void Item::attiva() {
    attivo = true ;
}


/*void Item::aggiornaItem() {
    if (attivo) {
        durata -= 1;
        if (durata <= 0)
            disattiva();
    }
}*/