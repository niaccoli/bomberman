#ifndef FUNZIONI_H
#define FUNZIONI_H
#include "Giocatore.h"
#include "Item.h"
#include "Bomba.h"
#include "Map.hpp"



//struct posizione{
//  int x[RAGGIO_MAX];
//  int y[RAGGIO_MAX];
//}

void muoviGiocatore(Giocatore& player, Map& m, char input) ;

void piazzaBomba(Giocatore& g, Bomba& b);
//posiziona una bomba nella posizione occupata dal giocatore e ne attiva il timer.

void gestisciInput(Giocatore& player, Bomba& b, Map& m, char input);
//precondizione: l'utente inserisce l'input da tastiera
//postcondizione: se input ('W''A''S''D') e posizione mossa valida la posizione del giocatore viene aggiornata, altrimenti
//mantiene la stessa posizione. Se input 'X' e non e' gia presente una bomba innescata,
//viene posizionata una bomba nella stessa posizione del giocatore.
//Se input non valido non viene effettuata alcuna azione.

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