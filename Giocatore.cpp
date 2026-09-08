#include "Giocatore.hpp"
#include "Personaggio.hpp"


Giocatore::Giocatore(): Personaggio(3,-1,-1) {
    invulnerabilitaOff();
    this -> punteggio = 0 ;
}

Giocatore::Giocatore(int vite, int x, int y): Personaggio(vite, x, y) {
    invulnerabilitaOff();
    this -> punteggio = 0 ;
}

Giocatore::Giocatore(int vite, Posizione posizione): Personaggio( vite, posizione ) {
    invulnerabilitaOff() ;
    this -> punteggio = 0 ;
}



void Giocatore::invulnerabilitaOn(int durata) {
    invulnerabilita = true;
    tempoInvulnerabilita += durata;
}

void Giocatore::invulnerabilitaOn( ) {
    invulnerabilita = true ;
    tempoInvulnerabilita += defaultTimerInvulnerabilitaMs ;
}


void Giocatore::invulnerabilitaOff() {
    invulnerabilita = false;
    tempoInvulnerabilita = 0;
}

bool Giocatore::invulnerabile() const {
    return invulnerabilita;
}


void Giocatore::aggiornaInvulnerabilita(int durata ) {
    if (invulnerabile()){
        tempoInvulnerabilita -= durata;

        if (tempoInvulnerabilita <= 0)
            invulnerabilitaOff();
    }
}

bool Giocatore::diminuisciVita() {
    if (! invulnerabile()) {
        Personaggio::diminuisciVita();
        return true ;
    }
    return false ;
}


bool Giocatore::diminuisciVita( int danno ) {
    if (! invulnerabile()) {
        Personaggio::diminuisciVita(danno);
        return true ;
    }
    return false ;
}



int Giocatore::getPunteggio() const{
    return this -> punteggio ;
}

void Giocatore::aumentaPunteggio( int punti ) {
    this -> punteggio += punti ;
}

