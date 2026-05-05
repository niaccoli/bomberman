#ifndef FUNZIONI_H
#define FUNZIONI_H

#include "Giocatore.h"
#include "Item.h"
#include "Bomba.h"

//bool posizioneValida(int x, int y); //serve sapere se una posizione è valida altrimenti il player non si deve spostare MATTE

void muoviGiocatore(Giocatore& player, char input);

void piazzaBomba(Giocatore& g, Bomba& b);

void gestisciInput(Giocatore& player,char input);

Item generaItem(int x, int y); //x e y sono la posizione di un nemico ucciso o di un muro rotto

void applicaEffettoItem( Item& i, Bomba& b); //a seconda del tipo di item andranno modificate le caratteristiche di bomba o giocatore
//capire se aggiungere un item che da invulnerabilità al giocatore



//void posizioneLiberaCasuale(int& x, int& y);
//serve una funzione che ritorni una posizione libera casuale sulla mappa per posizionare i nemici

//bool controlla collisioni(const Giocatore& player, const Nemico& nemici[])
//poi dovremo fare che un giocatore e un nemico occpano la stessa cella il giocatore perde una vita e il livello ricomincia

//bool controlla raccoltaItem




#endif