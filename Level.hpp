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

    Posizione posizioneRandomValida_v2() ;

    void posizionaNemici_v2( ) ;

    int isThereAnEnemy_v2( Posizione posizione) ;
    //se e' presente un nemico vivo in posizione ritorna l'indice del nemico, altrimenti ritorna -1 ;

public:
    Level(Map& m, int chasers_enemies, int items);

    Level(Map& m, int chasers_enemies, int random_enemies, int items);

    Level(Map& m, int chasers_enemies, int random_enemies, int tank_enemies, int items);

    Map& getMap( );

    bool updateLevel(Giocatore& g) ;
    /* MIA IDEA:
     * nel loop del main:
     * leggiInput
     *
    *  updateLevel:
    *       |--updateEnemies(muovi i nemici)
    *       |
    *       |--collisioneGiocatoreNemici
    *       |           \g ha subito danno -> return true -> reset
    *       |--updateBomba
    *       |            \b.esplode -> controllaCollisioniEsplosione. se g colpito return true
            |
            |--raccolta Item
            |
            |--return false ;

        chat:
    deve esserci un modo chiaro per sapere che “in questo turno la bomba è appena esplosa”.
    Quindi devi stare attento a non fare concettualmente:
    aggiornaBomba()

    if (b.innescata())
        collisioneEsplosione()

    MIA IDEA:
    fare una pdateLevel come bool e se il giocatore viene colpito ritornare subito true

    SUGGERIMENTO CHAT:
    C'è però una distinzione importante da fare adesso, prima di implementarla:
    vuoi riavviare il livello quando il giocatore viene "colpito" oppure quando perde effettivamente una vita?
    Non sono necessariamente la stessa cosa, visto che hai l'invulnerabilità.
    collisione
        ↓
    g.diminuisciVita()
        ↓
    return true
    Ma se Giocatore::diminuisciVita() non diminuisce la vita perché il giocatore è invulnerabile,
    la collisione restituisce comunque true.

    possibilità proposte da chat:
    A)void updateLevel() e poi controllare dal main lo stato del giocatore, per esempio confrontando le vite.
    B)Oppure potresti avere uno stato dentro Level, ad esempio un booleano: livelloDaResettare
    e poi:
    updateLevel(g)
i   f (level.daResettare())
    ...
    C)altra possibilità sarebbe restituire un int o un char per distinguere più risultati:
    0 → continua
    1 → giocatore colpito
    2 → livello completato
    3 → game over

    MIA IDEA( DOMANDA A CHAT )
    per adesso non considererei l'invulnerabilita' del giocatore, quella forse la implementeremo piu' avanti,
    e nel caso la mia idea sarebbe quella di aggiornare e collisioniGiocatoreNemici e Esplosione metteno negli
    if anche un parametro && !g.invulnerrabile( )

    RISPOSTA CHAT:
    aggiungere il controllo nella collisione tipo:
    è coerente, perché in quel caso stai dicendo: considero “collisione dannosa” solo una collisione che può
    effettivamente togliere vita.
    problema:
    Se Giocatore::diminuisciVita() già controlla internamente invulnerabile(), allora mettere anche && !g.invulnerabile()
    in tutte le collisioni diventa un doppio controllo.
    Hai quindi due modelli possibili:
    A) Collisione controlla invulnerabilità
       collisione -> se non invulnerabile -> diminuisciVita()
    B) Giocatore controlla invulnerabilità
       collisione -> diminuisciVita()
                             ↓
                     Giocatore decide
                     se perdere vita

    MIA IDEA:
    rendere diminuisci vita un bool

    RSIPOSTA CHAT:
    Sì, e nel tuo caso sarebbe una soluzione pulita.
    Potresti dare a diminuisciVita() questo significato:
    bool diminuisciVita();



    */


    void updateEnemies(Giocatore& g);
    //muove i nemici

    void updateItems( );
    //questa funzione avra' senso quando gli item avranno una durata

    bool collisioneGiocatoreNemici_v2(Giocatore& g ) ;

    bool collisioneEsplosione( Giocatore& g ) ;
    //precedentemente nominata come: bool collisioneEsplosioneMuriNemiciGiocatore_v2( Giocatore& g ) ;

    char raccoltaItem(Giocatore& g ) ;
    //se il giocatore occupa la stessa posizione di un Item attivo, l'item viene raccolto ( attivo == false) e applicato
    //l'effetto

    void dropItem(Posizione posizione) ; ;
    /*  Quando muore un nemico in (x,y) oppure viene distrutto un muro in (x,y), fai il lancio casuale:*/

    void piazzaBomba(Giocatore& g) ;
    //posiziona una bomba nella posizione occupata dal giocatore e ne attiva il timer (timer default = 4).

    //void applicaEffettoItem ( Item& i );
    //capire se mettere come funzione generale

    void reset_v2() ;

    void updateLevel( ) ;
    //aggiorna il timer dei potenziamenti sulle bombe
    //se vogliamo congelare il livello precedente  ma allo stesso tempo applicare l'effetto degli item a tutte le bombe
    //di tutti i livelli bisogna avere una funzione che aggiorni il timer degli effetti nei livelli dove non e' presente
    //il giocatore

    void applicaEffetto(char tipo ) ;
    //applica gli effetti sulle bombe

    // ---------------------------------------- DA VALUTARE---------------------------------------------

    //se vogliamo che se una bomba viene piazzata in un livello e il giocatore si sposta nel livello sucessivo la bomba
    //continui ad esplodere, i nemici si muovano e quando la bomba esplode crei danno ai nemici
    //richiede una funzione in BidirectionalLIst che prende la lista di livelli, chiama updateLevel(Giocatore& g)
    //per il livello corrente e updateLevel_v3( ) per gli altri livelli

    void updateLevel_v3 ( ) ;
    //chiama una versione moificata di updateEnemies ( muove i nemici ). Non essendo presente il giocatore in quel
    //livello fa muovere i nemici_inseguitore come nemici_random chiamando Nemico::nuovaPosizione( )

    void updateEnemies_v3( ) ;
    //muove tutti i nemici vivi nel livello. Non essendo presente il giocatore in quel
    //livello fa muovere i nemici_inseguitore come nemici_random chiamando Nemico::nuovaPosizione( )

    void collisioneEplosione_v3( ) ;
    //fa esplodere la bomba causando danno a muri e nemici

};