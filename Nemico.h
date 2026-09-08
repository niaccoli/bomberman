//
// Created by andre on 07/08/2026.
//

#ifndef BOMBERMAN_NEMICO_H
#define BOMBERMAN_NEMICO_H

#include "Giocatore.h"
#include "Map.hpp"
#include "Personaggio.hpp"

class Map ;


class Nemico : public Personaggio {
private:
    // Identifica la tipologia del nemico:
    // 'I' = nemico inseguitore
    // 'R' = nemico con movimento casuale
    // 'T' = nemico tank
    char tipo ;

    // Numero di punti assegnati al giocatore
    // quando il nemico viene sconfitto.
    int punti ;

    public:
    // Crea un nemico con una vita, senza tipo,
    // posizionato fuori dalla mappa e con valore in punti pari a zero.
        Nemico () ;

    // Crea un nemico del tipo specificato,
    // inizialmente posizionato fuori dalla mappa.
    // Il tipo determina anche il numero di vite
    // e i punti assegnati alla sua sconfitta.
        Nemico (char tipo) ;

    // Crea un nemico con vite, posizione e tipo specificati.
    // Il tipo determina comunque le caratteristiche
    // associate alla tipologia del nemico.
        Nemico (int vite, int x, int y, char tipo ) ;

    // Crea un nemico con vite, posizione e tipo specificati.
    // La posizione viene ricevuta tramite una struttura Posizione.
        Nemico (int vite, Posizione posizione, char tipo ) ;

    // Imposta la tipologia del nemico.
    // 'I' assegna 1 vita e 200 punti.
    // 'R' assegna 1 vita e 100 punti.
    // 'T' assegna 2 vite e 150 punti.
    // Se il tipo non è valido, assegna il carattere spazio
    // e imposta il valore in punti a zero.
        void setTipo ( char tipo ) ;

    // Restituisce la tipologia del nemico.
        char getTipo ( ) const;

    // Restituisce il numero di punti assegnati
    // alla sconfitta del nemico.
        int getPunti ( ) ;

    // Calcola quattro possibili posizioni per un nemico inseguitore,
    // ordinandole in base alla direzione del giocatore.
    // Le posizioni più favorevoli all'avvicinamento del giocatore
    // vengono inserite per prime nell'array possibili
        void nuovaPosizioneInseguitore (Giocatore& g, Posizione possibili[4]) const;

    // Calcola una possibile nuova posizione casuale del nemico.
    // Un nemico random tenta sempre un movimento casuale.
    // Un nemico tank ha invece una probabilità di rimanere fermo,
    // simulando una velocità di movimento inferiore.
    // Se il nemico si trova già sulla posizione del giocatore,
    // mantiene la posizione corrente.
        Posizione nuovaPosizioneCasuale (Giocatore& g) const;

    // Ripristina le vite del nemico in base alla sua tipologia:
    // 1 vita per inseguitori e random, 2 vite per i tank.
        void rianima( ) ;

};


#endif //BOMBERMAN_NEMICO_H