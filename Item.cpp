#include "Item.h"

Item::Item(): x(-1), y(-1), tipo(' '), durata(0), attivo(false){}

Item::Item(int x, int y, char tipo, int durata, bool attivo): x(x), y(y), tipo(tipo), durata(durata), attivo(attivo){}

void Item::setX(int x) {
    this->x = x;
}

void Item::setY(int y) {
    this->y = y;
}

int Item::getX() const {
    return this -> x;
}

int Item::getY() const {
    return this -> y;
}

void Item::setTipo(char tipo) {
    this -> tipo = tipo;
}

char Item::getTipo() const {
    return this -> tipo;
}

void Item::setDurata(int tempo) {
    this -> durata = tempo;
}

int Item::getDurata() const {
    return this -> durata;
}

bool Item::isAttivo() const{
    return this -> attivo;
}

void Item::raccogli() {
    disattiva();
}

void Item::disattiva() {
    attivo = false;
    setDurata(0);
}

void Item::aggiornaItem() {
    if (attivo) {
        durata -= 1;
        if (durata <= 0)
            disattiva();
    }
}