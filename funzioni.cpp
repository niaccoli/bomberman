#include "funzioni.h"
#include "Bomba.h"
#include <cstdlib>





void muoviGiocatore(Giocatore& player, char input) {
    int dx = 0;
    int dy = 0;

    if (input == 'w' || input == 'W')
        dy = -1;
    else if (input == 'a' || input == 'A')
        dx = -1;
    else if (input == 's' || input == 'S')
        dy = 1;
    else //chat suggerisce di aggiungere un if esle e un else con return (valutare: in realtà il controllo lo faccio gia sotto)
        dx = 1;

    int newX = player.getX() + dx;
    int newY = player.getY() + dy;

    //if mossavalida(newx,newy)

    player.muovi(newX, newY);
}

void piazzaBomba(Giocatore& g, Bomba& b) {
    b.setX(g.getX());
    b.setY(b.getY());
    b.setTimer(4);
    b.attiva();
}



void gestisciInput(Giocatore& player,Bomba& b,char input) {
    if (input == 'W' || input == 'w' || input == 'A' || input == 'a' || input == 's' || input == 'S' ||
        input == 'd' || input == 'D')
        muoviGiocatore(player, input);
    else if (input == 'x' || input == 'X') {
        if ( ! b.attivata())
        piazzaBomba(player,  b);
    }
    else
        return;
}



Item generaItem(int x, int y) { //"GLI ITEM MODIFICANO IL COMPORTAMENTO DELLE BOMBE AUMENTANDO IL RAGGIO PER UN TEMPO DI 5 O 10 SECONDI"
    //per ora:
    //'B' = aumento raggio bomba
    //'T' = diminuzione tempo esplosione
    //'D' = aumento danno bomba (creare nemici tank con 2 vite)
    //valutare se aggiungere: 'I' = invulnerabilità     'V'=aumento velocità?        punto vita? pistola?

    int i = rand() % 3;
    if (i == 0) {
        return Item( x, y, 'D', 20, true);
    }
    else if (i == 1) {
        return Item( x, y, 'B', 20, true);
    }
    else {
        return Item( x, y, 'T', 10, true);
    }
}

void applicaEffettoItem( Item& i, Bomba& b) { //quando il giocatore e l'item hanno la stessa posizione (bool controllaraccoltaitem())
    if (i.getTipo() == 'D') {
        b.attivaBoostRaggio();
    }
    else if (i.getTipo() == 'B') {
        b.attivaBoostDanno();
    }
    else {
        b.attivaBoostTimer();
    }
} //poi Item.raccogli();