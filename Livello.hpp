#include "Mappa.hpp"
#include "Item.hpp"
#include "Personaggio.hpp"
#include "Giocatore.hpp"
#include "Bomba.hpp"
#include "Nemico.hpp"
#include "Timer.hpp"
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

    // Indica se il livello è stato completato.
    bool completato;


    Timer visualize_explosion{0};
    //bool active_explosion = false;

    // Restituisce una posizione casuale valida in cui posizionare un nemico.
    // La posizione deve essere calpestabile, non occupata da altri nemici vivi,
    // sufficientemente lontana dall'entrata e non completamente circondata da muri.
    Posizione posizioneRandomValida() ;

    // Posiziona tutti i nemici del livello in posizioni casuali valide.
    void posizionaNemici( ) ;


    // Restituisce l'indice del nemico vivo presente nella posizione indicata.
    // Restituisce -1 se la posizione non è occupata da alcun nemico vivo.
    int isThereAnEnemy( Posizione posizione) ;



public:
    // Restituisce un riferimento alla bomba associata al livello.
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

    // Controlla se tutti i nemici del livello sono stati sconfitti.
    // Restituisce true se il livello è completato, false altrimenti.
    bool isCompletato( );

    // Aggiorna il timer della bomba.
    // Se il timer scade, gestisce l'esplosione e le relative collisioni.
    // Restituisce true se l'esplosione provoca una perdita di vita
    // al giocatore.
    bool aggiornaEsplosioni(Giocatore& g ,int durata ) ;

    // Aggiorna la posizione di tutti i nemici vivi del livello.
    // I nemici inseguitori cercano di avvicinarsi al giocatore,
    // mentre i nemici random e tank utilizzano il movimento casuale.
    // Evita inoltre che i nemici si spostino su muri,
    // altri nemici o sulla bomba attiva.
    void muoviNemici(Giocatore& g);

    // Controlla se il giocatore si trova nella stessa posizione
    // di un nemico vivo.
    // Restituisce true solo se la collisione provoca
    // effettivamente una perdita di vita al giocatore.
    bool collisioneGiocatoreNemici(Giocatore& g ) ;

    // Calcola tutte le celle raggiunte dall'esplosione della bomba.
    // Gestisce le collisioni con il giocatore, i nemici e i muri.
    // Distrugge i muri distruttibili, danneggia i nemici,
    // assegna il relativo punteggio e può generare item.
    // Restituisce true se il giocatore perde una vita.
    bool collisioneEsplosione( Giocatore& g ) ;

    // Controlla se il giocatore si trova nella posizione
    // di un item attivo.
    // Se l'item viene raccolto, lo disattiva e ne restituisce il tipo.
    // Restituisce ' ' se non viene raccolto alcun item.
    char raccoltaItem(Giocatore& g ) ;

    // Tenta casualmente di generare un item nella posizione indicata.
    // Se il drop avviene e sono ancora disponibili item,
    // assegna all'item posizione e tipo casuale e lo attiva.
    void dropItem(Posizione posizione) ;

    // Piazza la bomba nella posizione corrente del giocatore
    // e la innesca, solamente se non è già presente una bomba attiva.
    void piazzaBomba(Giocatore& g) ;

    // Disattiva la bomba del livello, rimuove tutti i suoi potenziamenti
    // e la riposiziona fuori dalla mappa.
    void resetBombeEPotenziamenti( ) ;

    // Riposiziona casualmente tutti i nemici del livello
    // e reimposta la bomba e i suoi potenziamenti.
    void reset_v3( ) ;

    // Aggiorna la durata dei potenziamenti della bomba.
    // I potenziamenti scaduti vengono automaticamente disattivati.
    void aggiornaPotenziamenti(int durata ) ;

    // Applica alla bomba il potenziamento corrispondente al tipo ricevuto:
    // 'D' aumenta il danno,
    // 'R' aumenta il raggio,
    // 'T' riduce il tempo necessario all'esplosione.
    void applicaEffetto(char tipo ) ;

};