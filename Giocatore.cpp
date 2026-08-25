#include "Giocatore.h"
#include "Personaggio.hpp"


Giocatore::Giocatore(): Personaggio(3,-1,-1) {
    invulnerabilitaOff();
}

Giocatore::Giocatore(int vite, int x, int y): Personaggio(vite, x, y) {
    invulnerabilitaOff();
}

Giocatore::Giocatore(int vite, Posizione posizione): Personaggio( vite, posizione ) {
    invulnerabilitaOff() ;
}



void Giocatore::invulnerabilitaOn(int durata) {
    invulnerabilita = true;
    tempoInvulnerabilita = durata;
}

void Giocatore::invulnerabilitaOn( ) {
    invulnerabilita = true ;
    tempoInvulnerabilita = 4 ;
}


void Giocatore::invulnerabilitaOff() {
    invulnerabilita = false;
    tempoInvulnerabilita = 0;
}

bool Giocatore::invulnerabile() const {
    return invulnerabilita;
}

void Giocatore::aggiornaInvulnerabilita(){
    if (invulnerabile()){
        tempoInvulnerabilita -= 1;

        if (tempoInvulnerabilita <= 0)
            invulnerabilitaOff();
    }
}

bool Giocatore::diminuisciVita() {
    if (! invulnerabile())
        Personaggio::diminuisciVita();
    return true ;
}



void Giocatore::diminuisciVita(int danno) {
    if (! invulnerabile())
            setVite( getVite() - danno);
}

