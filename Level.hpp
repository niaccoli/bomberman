#include "Map.hpp"
#include "Item.h"
#include "Personaggio.hpp"
#include "Giocatore.h"
#include "Bomba.h"
#include "Nemico.h"
#pragma once


const int MAX_NEMICI_INS = 10;
const int MAX_NEMICI_RND = 10;
const int MAX_NEMICI_TANK = 5;
const int MAX_ITEMS = 10;

class Level {
private:
    Map& map;

    Posizione cella_esplosione[9] ;
    int num_cella_esplosione ;

    Nemico nemici[MAX_NEMICI_INS + MAX_NEMICI_RND + MAX_NEMICI_TANK];
    int num_nemici ;
    int num_nemici_tank ;
    int num_nemici_ins ;
    int num_nemici_rnd ;

    Bomba b ;

    Item items[MAX_ITEMS];
    int num_items;
    int next_item ;

    bool completato;

    Timer visualize_explosion{0};
    bool active_explosion = false;

    Posizione posizioneRandomValida_v2() ;
    // Restituisce una posizione casuale calpestabile, non occupata da nemici vivi
    // e sufficientemente lontana dall'entrata del livello.

    void posizionaNemici_v2( ) ;
    // Posiziona tutti i nemici del livello in posizioni casuali valide.

    int isThereAnEnemy_v2( Posizione posizione) ;
    // Restituisce l'indice del nemico vivo presente nella posizione indicata;
    // restituisce -1 se la posizione non è occupata da alcun nemico vivo.


public:
    Level(Map& m, int random_enemies, int items);
    // Costruisce un livello con nemici inseguitori e un numero massimo di item.

    Level(Map& m, int chasers_enemies, int random_enemies, int items);
    // Costruisce un livello con nemici inseguitori, nemici random e un numero massimo di item.

    Level(Map& m, int chasers_enemies, int random_enemies, int tank_enemies, int items);
    // Costruisce un livello con nemici inseguitori, random, tank e un numero massimo di item.

    Map& getMap( );
    // Restituisce un riferimento alla mappa associata al livello.

    void stamp_map(Giocatore& g) ;
    // Visualizza lo stato corrente del livello; se è presente un'esplosione,
    // ne mostra le celle e successivamente ne azzera la memorizzazione.

    bool isCompletato( );
    // Restituisce true se tutti i nemici del livello sono stati sconfitti,
    // false altrimenti.

    bool updateLevel(Giocatore& g) ;
    // Aggiorna il livello corrente: muove i nemici, controlla le collisioni
    // con il giocatore e aggiorna la bomba e l'eventuale esplosione.
    // Restituisce true solo se il giocatore perde effettivamente una vita.


    void updateEnemies(Giocatore& g);
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

    void reset_v1( ) ;
    // Disattiva la bomba del livello, ne rimuove i potenziamenti
    // e la riposiziona fuori dalla mappa.

    void reset_v2( ) ;
    //riporta tutti i nemici vivi e li riposiziona casualmente, rimette gli item a 0 (da valuare), resetta la bomba
    //e ne disattiva eventuali potenziamenti

    void updateLevel( ) ;
    // Aggiorna la durata dei potenziamenti associati alla bomba del livello.

    void applicaEffetto(char tipo ) ;
    // Applica alla bomba il potenziamento identificato dal tipo ricevuto.

    // ---------------------------------------- DA VALUTARE---------------------------------------------

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

};