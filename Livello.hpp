#include "Mappa.hpp"
#include "Item.h"
#include "Personaggio.hpp"
#include "Giocatore.h"
#include "Bomba.h"
#include "Nemico.h"
#include "Timer.h"
#pragma once


const int MAX_NEMICI_INS = 10;
const int MAX_NEMICI_RND = 10;
const int MAX_NEMICI_TANK = 5;
const int MAX_ITEMS = 10;

class Livello {
private:
    // Mappa associata al livello.
    Mappa& mappa;

    // Celle interessate dall'ultima esplosione.
    Posizione cella_esplosione[9] ;

    // Numero di celle interessate dall'ultima esplosione.
    int num_cella_esplosione ;

    // Nemici presenti nel livello.
    Nemico nemici[MAX_NEMICI_INS + MAX_NEMICI_RND + MAX_NEMICI_TANK];

    // Numero totale di nemici presenti nel livello.
    int num_nemici ;

    // Numero di nemici tank.
    int num_nemici_tank ;

    // Numero di nemici inseguitori.
    int num_nemici_ins ;

    // Numero di nemici con movimento casuale.
    int num_nemici_rnd ;

    // Bomba associata al livello.
    Bomba b ;

    // Item disponibili nel livello.
    Item items[MAX_ITEMS];

    // Numero massimo di item che possono essere generati nel livello.
    int num_items;

    // Indice del prossimo item disponibile da generare.
    int next_item ;

    // Restituisce una posizione casuale calpestabile, non occupata
    // da nemici vivi e sufficientemente lontana dall'entrata.
    bool completato;


    Timer visualizza_esplosione{0};
    bool esplosione_attiva = false;


    Posizione posizioneRandomValida_v2() ;
    // Restituisce una posizione casuale calpestabile, non occupata da nemici vivi
    // e sufficientemente lontana dall'entrata del livello.

    void posizionaNemici_v2( ) ;
    // Posiziona tutti i nemici del livello in posizioni casuali valide.

    int isThereAnEnemy_v2( Posizione posizione) ;
    // Restituisce l'indice del nemico vivo presente nella posizione indicata;
    // restituisce -1 se la posizione non è occupata da alcun nemico vivo.


public:
    Bomba& getBomb();

    Livello(Mappa& m, int random_enemies, int items);
    // Costruisce un livello con nemici inseguitori e un numero massimo di item.

    Livello(Mappa& m, int chasers_enemies, int random_enemies, int items);
    // Costruisce un livello con nemici inseguitori, nemici random e un numero massimo di item.

    Livello(Mappa& m, int chasers_enemies, int random_enemies, int tank_enemies, int items);
    // Costruisce un livello con nemici inseguitori, random, tank e un numero massimo di item.

    //Distruttore classe Level
    ~Livello();

    Mappa& getMap( );
    // Restituisce un riferimento alla mappa associata al livello.

    void stampaMappa(Giocatore& g, int timer_gioco) ;
    // Visualizza lo stato corrente del livello; se è presente un'esplosione,
    // ne mostra le celle e successivamente ne azzera la memorizzazione.

    bool isCompletato( );
    // Restituisce true se tutti i nemici del livello sono stati sconfitti,
    // false altrimenti.

    //bool updateLevel(Giocatore& g) ;
    // Aggiorna il livello corrente: muove i nemici, controlla le collisioni
    // con il giocatore e aggiorna la bomba e l'eventuale esplosione.
    // Restituisce true solo se il giocatore perde effettivamente una vita.



    bool aggiornaEsplosioni(Giocatore& g ,int durata ) ;

    void muoviNemici(Giocatore& g);
    // Aggiorna la posizione di tutti i nemici vivi del livello.

    void updateItems( );
    // Aggiorna lo stato degli item del livello.
    // Attualmente predisposta per una futura gestione degli item con durata.

    bool collisioneGiocatoreNemici_v2(Giocatore& g ) ;
    // Controlla la collisione tra giocatore e nemici.
    // Restituisce true solo se la collisione provoca effettivamente una perdita di vita.

    bool collisioneEsplosione( Giocatore& g ) ;
    // Calcola l'area dell'esplosione, gestisce le collisioni con giocatore,
    // nemici e muri e restituisce true se il giocatore perde una vita.
    //precedentemente nominata come: bool collisioneEsplosioneMuriNemiciGiocatore_v2( Giocatore& g ) ;

    char raccoltaItem(Giocatore& g ) ;
    // Se il giocatore si trova su un item attivo, ne restituisce il tipo;
    // restituisce ' ' se non è presente alcun item raccoglibile.

    void dropItem(Posizione posizione) ; ;
    // Tenta di generare casualmente un item nella posizione indicata,
    // se non è stato raggiunto il numero massimo di item del livello.

    void piazzaBomba(Giocatore& g) ;
    // Piazza e innesca la bomba nella posizione del giocatore,
    // se non è già presente una bomba attiva.

    void resetBombeEPotenziamenti( ) ;
    // Disattiva la bomba del livello, ne rimuove i potenziamenti
    // e la riposiziona fuori dalla mappa.

    void reset_v3( ) ;

    void aggiornaPotenziamenti(int durata ) ;

    void applicaEffetto(char tipo ) ;
    // Applica alla bomba il potenziamento identificato dal tipo ricevuto.

    /* ---------------------------------------- DA VALUTARE---------------------------------------------

    //se vogliamo che se una bomba viene piazzata in un livello e il giocatore si sposta nel livello sucessivo la bomba
    //continui ad esplodere, i nemici si muovano e quando la bomba esplode crei danno ai nemici
    //richiede una funzione in BidirectionalLIst che prende la lista di livelli, chiama updateLevel(Giocatore& g)
    //per il livello corrente e updateLevel_v3( ) per gli altri livelli

    void updateLevel_v3 ( ) ;
    //chiama una versione modificata di updateEnemies ( muove i nemici ). Non essendo presente il giocatore in quel
    //livello fa muovere i nemici_inseguitore come nemici_random chiamando Nemico::nuovaPosizione( )

    void updateEnemies_v3( ) ;
    //muove tutti i nemici vivi nel livello. Non essendo presente il giocatore in quel
    //livello fa muovere i nemici_inseguitore come nemici_random chiamando Nemico::nuovaPosizione( )

    void collisioneEplosione_v3( ) ;
    //fa esplodere la bomba causando danno a muri e nemici
    */

};