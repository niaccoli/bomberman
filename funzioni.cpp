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
    b.attivaBomba();
}



void gestisciInput(Giocatore& player,Bomba& b,char input) {
    if (input == 'W' || input == 'w' || input == 'A' || input == 'a' || input == 's' || input == 'S' ||
        input == 'd' || input == 'D')
        muoviGiocatore(player, input);
    else if (input == 'x' || input == 'X') {
        if ( ! b.innescata())
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

/*void applicaEffettoItem( Item& i, Bomba& b) { //quando il giocatore e l'item hanno la stessa posizione (bool controllaraccoltaitem())
    if (i.getTipo() == 'D') {
        b.attivaBoostRaggio();
    }
    else if (i.getTipo() == 'B') {
        b.attivaBoostDanno();
    }
    else {
        b.attivaBoostTimer();
    }
} //poi Item.raccogli();*/


/*void collisioneGiocatoreNemici (Giocatore& g, Nemico& nemici[]){
 *  for (tutti i nemici)
 *      if (giocatore.posizione == nemico.posizione)
 *          giocatore.diminuisci_vita
 *}

/*void collisioneEsplosione(Giocatore& g, Nemico& n[], Mappa& m, Bomba& b);{
 *prende la posizione della bomba
 *prende il raggio della bomba
 *calcola
 *controlla cella per cella
 *se una cella(x,y) == giocatore.posizione
 *      giocatore.diminuisci vita
 *se una cella(x,y) == nemico.posizione
 *      nemico.diminuisci vita
 *se una cella(x, y) == muro distruttibile
 *      muro.distruggi
}*/

//void raccoltaItem(Giocatore& g, Item& i[], Bomba& b) {
//  for(tutti gli item(
//      se giocatore.posizione == item.posizione && item.attivo
//          item.raccogli;
//  applica_effetto_item(i[i], b)
//}


/*void controllaCollisioni(Giocatore& g, Nemico& n[], Mappa& m, Bomba& b, Item i){
 *  collisioneGiocatoreNemici(g, n);
 *  if (giocatore.vivo()) //valutare se lasciare questo controllo, solo che senza la vita del giocatore potrebbe andare in negativo se dopo si prende anche una bomba
 *      if (b.innescata() && bomba.getTimer <= 0)
 *          collisioneEsplosione(g, n, m, b);
 *  if (giocatore.vivo())
 *      raccoltaItem(g, i, b)
 }*/

