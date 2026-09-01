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





void posizionaGiocatoreStart( Giocatore& player, BidirectionalList& l ) ;
//posiziona il giocatore all'entrata del livello corrente
//puo' essere utile anche per un eventale reset


void controllaPassaggioLivelli( Giocatore& player, BidirectionalList& l ) ;


void reset_v1( Giocatore& player, BidirectionalList& l ) ;
//attiva l'invulnerabilita' del giocatore, disattiva i potenziamenti sulle bombe


int min(int n1, int n2, int n3, int n4 ) ;


#endif