#include "Giocatore.h"
#include "Personaggio.hpp"


Giocatore::Giocatore(): Personaggio(3,-1,-1) {
    invulnerabilitaOff();
}

Giocatore::Giocatore(int vite, int x, int y): Personaggio(vite, x, y) {
    invulnerabilitaOff();
}


void Giocatore::invulnerabilitaOn(int durata) {
    invulnerabilita = true;
    tempoInvulnerabilita = durata;
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

void Giocatore::diminuisciVita() {
    if (! invulnerabile())
        Personaggio::diminuisciVita();
}

void Giocatore::diminuisciVita(int danno) {
    if (! invulnerabile())
        //if (getvite() - danno)
            setVite( getVite() - danno);
    //else
    //setvite()=0
}

