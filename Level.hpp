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

    void updateEnemies(Personaggio& p);

    void updateItems(Item& i);
    //questa funzione avra' senso quando gli item avranno una durata

    bool collisioneGiocatoreNemici_v2(Giocatore& g ) ;

    bool collisioneEsplosione( Giocatore& g ) ;
    //precedentemente nominata come: bool collisioneEsplosioneMuriNemiciGiocatore_v2( Giocatore& g ) ;

    void raccoltaItem(Giocatore& g ) ;
    //se il giocatore occupa la stessa posizione di un Item attivo, l'item viene raccolto ( attivo == false) e applicato
    //l'effetto

    void dropItem(Posizione posizione) ; ;
    /*  Quando muore un nemico in (x,y) oppure viene distrutto un muro in (x,y), fai il lancio casuale:*/

    void piazzaBomba(Giocatore& g) ;
    //posiziona una bomba nella posizione occupata dal giocatore e ne attiva il timer (timer default = 4).

    //void applicaEffettoItem ( Item& i );
    //capire se mettere come funzione generale

    void reset_v2() ;

};