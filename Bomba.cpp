#include "Bomba.h"

Bomba::Bomba(): x(-1), y(-1), timer(4), danno(1), raggio(1), attivo(false), boostDanno(false), durataBoostDanno(5),
                boostRaggio(false), durataBoostRaggio(5), boostTimer(false), durataBoostTimer(5){}


/*Bomba::Bomba(int x, int y, int timer, int danno, int raggio, bool attivo) {
    setX(x);
    setY(y);
    setTimer(timer);
    setDanno(danno);
    setRaggio(raggio);
    setAttivo(attivo);
}*/

int Bomba::getX() const {
    return this -> x;
}

int Bomba::getY() const {
    return this -> y;
}

void Bomba::setX(int x) {
    this -> x = x;
}

void Bomba::setY(int y) {
    this -> y = y;
}

int Bomba::getTimer() const {
    return this -> timer;
}

void Bomba::setTimer(int tempo) {
    this -> timer = tempo;
}

void diminuisciTimer() {
    this -> timer -= 1;
}

void Bomba::dimezzaTimer() {
    this -> timer /= 2;
}

int Bomba::getDanno() const {
    return this -> danno;
}

void Bomba::setDanno(int danno) {
    this -> danno = danno;
}

void Bomba::duplicaDanno() {
    this -> danno *= 2;
}

int Bomba::getRaggio() const {
    return this -> raggio;
}

void Bomba::setRaggio(int raggio) {
    this -> raggio = raggio;
}

void Bomba::raddoppiaRaggio() {
    this -> raggio *= 2;
}

bool Bomba::attivata() const {
    return this -> attivo;
}

void setAttivo(bool attivo) {
    this -> attivo = attivo;
}

void Bomba::attiva() {
    this -> attivo = true;
}

void Bomba::disattiva() {
    this -> attivo = false;
}

void Bomba::aggiornaBomba() {
    aggiornaBoostDanno();
    aggiornaBoostRaggio();
    aggiornaBoostTimer();
    if (attivata()) {
        diminuisciTimer();
        if (getTimer() <= 0)
            disattiva();
    }
}




void Bomba::attivaBoostDanno() {
    boostDanno = true;
    setDurataBoostDanno(5);
    duplicaDanno();
}

void Bomba::disattivaBoostDanno() {
    boostDanno = false;
    danno = 1;
}

void Bomba::setDurataBoostDanno(int durata) {
    durataBoostDanno = durata;
}

int Bomba::getDurataBoostDanno() const {
    return durataBoostDanno;
}

bool Bomba::boostDannoAttivo() const {
    return boostDanno;
}

void Bomba::aggiornaBoostDanno() {
    if (boostDannoAttivo()) {
        diminuisciDurataBoostDanno();
        if (getDurataBoostDanno() <= 0)
            disattivaBoostDanno();
    }
}


void Bomba::attivaBoostRaggio() {
    boostRaggio = true;
    setDurataBoostRaggio(5);
    raddoppiaRaggio();
}

void Bomba::disattivaBoostRaggio() {
    boostRaggio = false;
    raggio = 1;
}
void Bomba::setDurataBoostRaggio(int durata) {
    durataBoostRaggio = durata;
}

int Bomba::getDurataBoosRaggio() const {
    return durataBoostRaggio;
}
bool Bomba::boostRaggioAttivo() {
    return boostRaggio;
}

void Bomba::aggiornaBoostRaggio() {
    if (boostRaggioAttivo()) {
        diminuisciDurataBoostRaggio();
        if (getDurataBoosRaggio() <= 0)
            disattivaBoostRaggio();
    }
}

void Bomba::attivaBoostTimer() {
    boostTimer = true;
    setDurataBoostTimer(5);
    dimezzaTimer();
}

void Bomba::disattivaBoostTimer() {
    boostTimer = false;
    timer = 1;
}

void Bomba::setDurataBoostTimer(int durata) {
    durataBoostTimer = durata;
}

int Bomba::getDurataBoostTimer() const {
    return durataBoostRaggio;
}

bool Bomba::boostTimerAttivo() {
    return boostTimer;
}

void Bomba::aggiornaBoostTimer() {
    if (boostTimerAttivo()) {
        diminuisciDurataBoostTimer();
        if (getDurataBoostTimer() <= 0)
            disattivaBoostTimer();
    }
}