#include "Map.hpp"
#include "Item.h"
#include "Personaggio.hpp"
#include "Giocatore.h"
#include "Bomba.h"
#include "NemicoInseguitore.h"
#include "NemicoRandom.h"
#pragma once

const int MAX_NEMICI_INS = 10;
const int MAX_NEMICI_RND = 10;
const int MAX_ITEMS = 10;

class Level{

private:
    Map& map;

    NemicoInseguitore nemici_inseguitore[MAX_NEMICI_INS];
    int num_nemici_ins;

    NemicoRandom nemici_random[MAX_NEMICI_RND];
    int num_nemici_rnd;

    Bomba b ;

    Item items[MAX_ITEMS];
    int num_items;

    bool completato;

    /* valutare se avere un solo oggetto Bomba per il giocatore, riutilizzato ogni volta.
    *   Giocatore g;
        Bomba b;
        BidirectionalList livelli;
    La bomba esiste una sola volta e cambia stato:
    Quando esplode, la disattivi e la stessa b può essere riutilizzata per la bomba successiva.


    problema: "non c'e la possibilita che se la bomba viene piazzata in un livello poi il giocatore va in un altro
    livello prima che la bomba esploda poi la bomba risulti posizionata nel nuovo livello?"

    Sì, è esattamente un problema possibile con l'impostazione “una sola Bomba globale”.
    Esempio:

    Sei nel livello 1.
    Piazzi la bomba in (5, 7).
    La bomba rimane attiva per 4 secondi.
    Prima che esploda passi al livello 2.

    La soluzione più coerente : Se vuoi mantenere una sola bomba, la bomba deve ricordarsi in quale livello è stata piazzata.
     *
     *
    !!! una bomba per livello è probabilmente la soluzione più naturale per la struttura che state costruendo.
    Level 1
        ├── Map
        ├── Nemici
        ├── Item
        └── Bomba

    Level 2
        ├── Map
        ├── Nemici
        ├── Item
        └── Bomba

    Quando sei nel livello 1: current->level->piazzaBomba(g);

    domanda: "se la bomba e stata piazzata e il giocatore si muove di livello e' giusto che la bomba esploda e faccia danno lo stesso?"

    la bomba del livello 1 viene attivata. Se poi passi al livello 2, la bomba resta comunque dentro Level 1.
    C'è però un dettaglio progettuale importante. Se vuoi che:

    la bomba continui il countdown anche mentre il giocatore è in un altro livello
    non puoi aggiornare il timer solo sul livello corrente.

    Per esempio, se il main facesse solo:
    current->level->update();
    la bomba nel livello precedente smetterebbe di essere aggiornata quando cambi livello.

    due possibilità:

    1. I livelli inattivi continuano a vivere
    Aggiornate anche le bombe attive degli altri livelli.
    La bomba esplode dopo 4 secondi indipendentemente da dove si trovi il giocatore.

    2. I livelli vengono "congelati" quando li lasci
    Quando torni nel livello, tutto riprende da dove era rimasto: nemici, bomba, timer ecc.

    non farei più appartenere la bomba al giocatore. La bomba viene piazzata dal giocatore,
    ma una volta piazzata appartiene allo stato del livello, proprio come un item o un nemico. */

public:
    Level() ; //ANDREA

    Level(Map& m, int chasers_enemies, int random_enemies, int items);

    Map& getMap();

    void addEnemies(Personaggio& p);

    void updateEnemies(Personaggio& p);

    void addItem(Item& i);

    void updateItems(Item& i);

    //nel vostro progetto ha senso che la gestione delle collisioni appartenga a Level, perché è Level che conosce gli
    //oggetti presenti nel livello: mappa, nemici e item.
    //più pulito rispetto a passare continuamente Level& alle funzioni.
    //Level possiede/conosce nemici, item e mappa;
    //quindi una funzione che deve controllare tutti i nemici del livello dovrebbe poter usare direttamente i membri del livello;
    //non serve esporre getNemico(i), getNumNemici(), ecc. solo per permettere a una funzione esterna di fare il controllo;


    void collisioneGiocatoreNemici(Giocatore& g ) ;
    void collisioneEsplosione(Giocatore& g ) ;
    void raccoltaItem(Giocatore& g ) ;

    void controllaCollisioni(Giocatore& g ) ;

    void dropItem(int x, int y) ;
    //guarda nore in item.h
    /*  si occupa di:
        1. controllare num_items > 0
        2. stabilire casualmente se fare il drop
        3. prendere items[num_items - 1]
        4. assegnare tipo casuale
        5. assegnare x e y
        6. attivarlo
        7. decrementare num_items


        //non considerare muri per ora
        Quando muore un nemico in (x,y) oppure viene distrutto un muro in (x,y), fai il lancio casuale:
        nemico muore
             ↓
        rand()
             ↓
        drop item?
          /      \
        NO        SI
                  ↓
           ci sono ancora item?
               /       \
              NO       SI
                        ↓
               prendi items[num_item - 1]
               spostalo in (x,y)
               attivo = true
                setTipoRandom()
               next_item++
        */

    void piazzaBomba(Giocatore& g) ;

    void applicaEffettoItem ( Item& i );


};