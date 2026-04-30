#include "Giocatore.h "
#include "Personaggio.hpp"


Giocatore::Giocatore(): Personaggio(3,-1,-1) {
    InvulnerabilitaOff();
}

Giocatore::Giocatore(int vite, int x, int y): Personaggio(vite, x, y) {
    InvulnerabilitaOff();
}


void Giocatore::InvulnerabilitaOn() {
    invulnerabilita = true;
}

void Giocatore::InvulnerabilitaOff() {
    invulnerabilita = false;
}

bool Giocatore::invulnerabile() const {
    return invulnerabilita;
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


void muoviGiocatore(Giocatore &player, char input) {
    int dx = 0;
    int dy = 0;

    if (input == 'w' || input == 'W')
        dy = -1;
    else if (input == 'a' || input == 'A')
        dx = -1;
    else if (input == 's' || input == 'S')
        dy = 1;
    else
        dx = 1;

    int newX = player.getX() + dx;
    int newY = player.getY() + dy;

    //if mossavalida(newx,newy)

    player.muovi(newX, newY);
}