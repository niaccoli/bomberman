#ifndef FUNZIONI_H
#define FUNZIONI_H
#include "Giocatore.h"
#include "Item.h"
#include "Bomba.h"
#include "Level.hpp"
#include "BidirectionalList.hpp"



void muoviGiocatore(Giocatore& player, BidirectionalList& lista_livelli, char input) ;
//valutare se non fare una cosa simile a nemico
//ovvero fai una funzione leggi input
//passi l'input a nuovaPosizione, una volta calcolata la nuova posizione e' level ad occuparsi se il giocatore
//puo' muoversi o no







void gestisciInput(Giocatore& player,BidirectionalList& lista_livelli, char input);
//precondizione: l'utente inserisce l'input da tastiera
//postcondizione: se input ('W''A''S''D') e posizione mossa valida la posizione del giocatore viene aggiornata, altrimenti
//mantiene la stessa posizione. Se input 'X' e non e' gia presente una bomba innescata,
//viene posizionata una bomba nella stessa posizione del giocatore.
//Se input non valido non viene effettuata alcuna azione.



//Item generaItem(int x, int y); //x e y sono la posizione di un nemico ucciso o di un muro rotto
//sostituita da dropItem in class::Level




//anche questa funzione ha piu' senso appartenga al livello
/*chat dice: è il livello che:
possiede gli item;
possiede la bomba;
controlla quando il giocatore collide con un item.

Level::controllaCollisioni(...)
        ↓
controlla se player è sopra un Item
        ↓
Level::raccogliItem(...)
        ↓
Level::applicaEffettoItem(...)
        ↓
item.raccogli()

Il main dovrebbe limitarsi più o meno a:

level->controllaCollisioni(player);

e lasciare che Level sappia cosa fare con i suoi oggetti.


DOBBIAMO DECIDERE SE I POTENZIAMENTI SULLE BOMBE APPARTENGONO AL LIVELLO O AL GIOCATORE:
A. Il bonus appartiene al livello
prendo +raggio nel Level 1
→ solo la bomba del Level 1 ha raggio maggiore

B. Il bonus appartiene al giocatore
prendo +raggio nel Level 1
→ da ora tutte le bombe che piazzo hanno raggio maggiore
→ anche nel Level 2, Level 3...
*/











#endif