#ifndef MAPPA_HPP
#define MAPPA_HPP
#include <curses.h>
#include "Personaggio.hpp"
#include "Nemico.hpp"
#include "Bomba.hpp"
#include "Item.hpp"

// Forward declaration: comunica l'esistenza della classe Nemico al compilatore prima della sua completa definizione
class Nemico ; 


class Mappa{
protected:
    int rows;
    int cols;
    char** grid;
    WINDOW* win;
    Posizione entry ;
    Posizione exit ;

public:
    // --- Costruttori ---

    // Costruttore: alloca dinamicamente la matrice della mappa e inizializza la finestra ncurses.
    Mappa(int h, int w);


    //Distruttore classe Mappa
    ~Mappa();


    // Carica la configurazione strutturale della mappa dal file di testo corrispondente all'ID del livello (es. level1.txt).
    void inizializzaMappa(int levelID);
    
    // Restituisce il carattere memorizzato nella griglia statica alle coordinate specificate.
    char getCell(Posizione position);
    
    // Imposta manualmente un carattere nella griglia statica.
    void setCell(int x, int y, char c);
    
    // Versione overload: chiama la funzione di stampa principale passando array nulli per le celle di esplosione.
    void stampaMappa(const Giocatore& p, const Nemico nemici[], int numNemici, const Item items[], int numItems, const Bomba& b, int timer_gioco);

    // Gestisce il rendering completo della mappa centrata a schermo, il refresh delle statistiche e il posizionamento dinamico di tutte le entità.
    void stampaMappa(const Giocatore& p, const Nemico nemici[], int numNemici, const Item items[], int numItems,
        const Bomba& b , Posizione celle_esplosione[], int num_celle_esplosione, int timer_gioco);

    // Verifica se le coordinate passate non puntano a un muro (sia distruttibile che indistruttibile) o a una bomba. Ritorna true se lo spazio è percorribile.
    bool isCamminabile (Posizione posizione ) ; 
    bool isCamminabile (int x, int y ) ;
    bool mossavalida(int x, int y);

    // Genera una coordinata causale e valida all'interno della mappa che sia calpestabile, escludendo i muri.
    Posizione posizioneCamminabileRandom( ) ; 

    // Verifica che la posizione indicata sia priva di muri (# o X). Ritorna false in caso di ostacolo.
    bool cellaSenzaMuro(int x, int y);

    // Verifica se una posizione è circondata completamente o parzialmente da ostacoli fisici (muri).
    bool isCircondataDaMuri(Posizione p);

    // Rimuove un muro distruttibile (X) trasformandolo in uno spazio vuoto ( ).
    void distruggiMuro(Posizione posizione) ;
    void distruggiMuro();

    // Ritorna true se la posizione passata corrisponde a un muro distruttibile ('X').
    bool isDistruttibile( Posizione posizione ) ; 

    // Ritorna true se la posizione passata corrisponde a un muro indistruttibile ('#').
    bool isMuroIndistruttibile ( Posizione posizione ) ; 

    // Restituisce il numero totale di righe della mappa.
    int getRighe();

    // Restituisce il numero totale di colonne della mappa.
    int getCols();
    
    // Restituisce il puntatore alla finestra ncurses corrente utilizzata per il rendering della mappa.
    WINDOW* getWin();

    // Restituisce le coordinate del punto di ingresso ('@').
    Posizione getEntrata();

    // Restituisce le coordinate del punto di uscita ('U').
    Posizione getUscita();

    // Verifica se la posizione fornita corrisponde esattamente al punto d'ingresso della mappa.
    bool isEntrata( Posizione posizione);

    // Verifica se la posizione fornita corrisponde esattamente al punto di uscita della mappa.
    bool isUscita( Posizione posizione);

    // Verifica se una determinata posizione rientra nell'area circostante la porta d'ingresso.
    bool isVicinoEntrata( Posizione posizione );

};
#endif