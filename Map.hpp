#ifndef MAP_HPP
#define MAP_HPP
#include <curses.h>
#include "Personaggio.hpp"
#include "Nemico.h" 
#include "Bomba.h"
#include "Item.h"

// Forward declaration: comunica l'esistenza della classe Nemico al compilatore prima della sua completa definizione
class Nemico ; 


class Map{
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
    Map(int h, int w);


    // Carica la configurazione strutturale della mappa dal file di testo corrispondente all'ID del livello (es. level1.txt).
    void Initialize_Map(int levelID);
    
    // Restituisce il carattere memorizzato nella griglia statica alle coordinate specificate.
    char getCell(Posizione position);
    
    // Imposta manualmente un carattere nella griglia statica.
    void setCell(int x, int y, char c);
    
    // Versione overload: chiama la funzione di stampa principale passando array nulli per le celle di esplosione.
    void stamp_map(const Giocatore& p, const Nemico nemici[], int numNemici, const Item items[], int numItems, const Bomba& b, int timer_gioco);

    // Gestisce il rendering completo della mappa centrata a schermo, il refresh delle statistiche e il posizionamento dinamico di tutte le entità.
    void stamp_map(const Giocatore& p, const Nemico nemici[], int numNemici, const Item items[], int numItems,
        const Bomba& b , Posizione celle_esplosione[], int num_celle_esplosione, int timer_gioco);

    // Verifica se le coordinate passate non puntano a un muro (sia distruttibile che indistruttibile) o a una bomba. Ritorna true se lo spazio è percorribile.
    bool isWalkable (Posizione posizione ) ; 
    bool isWalkable (int x, int y ) ;
    bool mossavalida(int x, int y);

    // Genera una coordinata causale e valida all'interno della mappa che sia calpestabile, escludendo i muri.
    Posizione walkableRandomPosition( ) ; 

    // Verifica che la posizione indicata sia priva di muri (# o X). Ritorna false in caso di ostacolo.
    bool cell_without_wall(int x, int y);

    // Verifica se una posizione è circondata completamente o parzialmente da ostacoli fisici (muri).
    bool isSurroundedByWalls(Posizione p);

    // Rimuove un muro distruttibile (X) trasformandolo in uno spazio vuoto ( ).
    void breakWall(Posizione posizione) ;
    void breakWall();

    // Ritorna true se la posizione passata corrisponde a un muro distruttibile ('X').
    bool isBreakable( Posizione posizione ) ; 

    // Ritorna true se la posizione passata corrisponde a un muro indistruttibile ('#').
    bool isUnbreakableWall ( Posizione posizione ) ; 

    // Restituisce il numero totale di righe della mappa.
    int getRows();

    // Restituisce il numero totale di colonne della mappa.
    int getCols();
    
    // Restituisce il puntatore alla finestra ncurses corrente utilizzata per il rendering della mappa.
    WINDOW* getWin();

    // Restituisce le coordinate del punto di ingresso ('@').
    Posizione getEntry( );

    // Restituisce le coordinate del punto di uscita ('U').
    Posizione getExit ( );

    // Verifica se la posizione fornita corrisponde esattamente al punto d'ingresso della mappa.
    bool isEntry( Posizione posizione);

    // Verifica se la posizione fornita corrisponde esattamente al punto di uscita della mappa.
    bool isExit( Posizione posizione);

    // Verifica se una determinata posizione rientra nell'area circostante la porta d'ingresso.
    bool isNearEntry( Posizione posizione );

};
#endif