#ifndef FUNZIONI_H
#define FUNZIONI_H
#include "Giocatore.h"
#include "Item.h"
#include "Bomba.h"



//struct posizione{
//  int x[RAGGIO_MAX];
//  int y[RAGGIO_MAX];
//}

//bool posizioneValida(int x, int y); //serve sapere se una posizione è valida altrimenti il player non si deve spostare MATTE

void muoviGiocatore(Giocatore& player, char input);

void piazzaBomba(Giocatore& g, Bomba& b);

void gestisciInput(Giocatore& player,char input);

Item generaItem(int x, int y); //x e y sono la posizione di un nemico ucciso o di un muro rotto

void applicaEffettoItem( Item& i, Bomba& b); //a seconda del tipo di item andranno modificate le caratteristiche di bomba o giocatore
//capire se aggiungere un item che da invulnerabilità al giocatore
//nel caso aggiungerlo nei parametri


//void posizioneLiberaCasuale(int& x, int& y);
//ritorni una posizione libera casuale sulla mappa per posizionare i nemici

//void collisioneGiocatoreNemici (Giocatore& g, Nemico& nemici[]);

//void collisioneEsplosione(Giocatore& g, Nemico& n[], Mappa& m, Bomba& b);

//void raccoltaItem( Giocatore& g, Item& i[]);

//void controllaCollisioni(Giocatore& g, Nemico& n[], Mappa& m, Bomba& b, Item i[]);






#endif