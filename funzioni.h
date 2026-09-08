#ifndef FUNZIONI_H
#define FUNZIONI_H
#include "Giocatore.h"
#include "Item.h"
#include "Bomba.h"
#include "Level.hpp"
#include "BidirectionalList.hpp"


// Calcola la nuova posizione del giocatore in base al comando ricevuto.
// Il giocatore viene spostato solo se la posizione è calpestabile
// e non è occupata da una bomba attiva.
void muoviGiocatore(Giocatore& player, BidirectionalList& lista_livelli, char input) ;

// Gestisce il comando ricevuto dal giocatore.
// I tasti W, A, S e D muovono il giocatore,
// mentre X piazza una bomba se non ne è già presente una attiva.
// Gli altri input vengono ignorati.
void gestisciInput(Giocatore& player,BidirectionalList& lista_livelli, char input);

// Mostra a schermo le informazioni relative alla partita:
// vite e punteggio del giocatore, tempo rimanente
// e potenziamenti della bomba attualmente attivi.
void StampInfo(const Giocatore& player, const Bomba& b, int map_cols, int timer_gioco);

// Posiziona il giocatore nella prima cella interna
// adiacente all'entrata del livello corrente.
void posizionaGiocatoreStart( Giocatore& player, BidirectionalList& l ) ;


// Controlla se il giocatore ha raggiunto l'entrata o l'uscita
// del livello corrente.
// Se possibile, aggiorna il livello corrente e posiziona
// il giocatore accanto all'ingresso corrispondente del nuovo livello.
void controllaPassaggioLivelli( Giocatore& player, BidirectionalList& l ) ;

// Reimposta lo stato delle bombe e dei relativi potenziamenti
// e attiva temporaneamente l'invulnerabilità del giocatore.
void reset_v1( Giocatore& player, BidirectionalList& l ) ;

// Reimposta lo stato dei livelli dopo che il giocatore è stato colpito
// e riposiziona il giocatore all'inizio del livello corrente.
void reset_v3(Giocatore& player, BidirectionalList& l ) ;

// Restituisce il valore minimo tra i quattro interi ricevuti.
int min(int n1, int n2, int n3, int n4 ) ;

void popupGiocatoreColpito();


#endif