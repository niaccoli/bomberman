#include "Level.hpp"
#include "funzioni.h"
#include <cstdlib>
#include "Map.hpp"


Level::Level(Map& m, int chasers_enemies, int random_enemies, int items) : map(m){

    if ( chasers_enemies >= 0 && chasers_enemies <= MAX_NEMICI_INS)
        num_nemici_ins = chasers_enemies ; //indica il numero di nemici_ins "validi" ma ancora non posizionati
    else
        num_nemici_ins = 0 ;

    if ( random_enemies >= 0 && random_enemies <= MAX_NEMICI_RND)
        num_nemici_rnd = random_enemies ; //indica il numero di nemici_rnd "validi" ma ancora non posizionati
    else
        num_nemici_rnd = 0 ;

    posizionaNemici() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    completato = false;
}

/*IMPLEMENTAZIONE CON NEMICO ---------------------------------------------------------------------------------------

Level::Level(Map& m, int chasers_enemies int items) : map(m) {

    num_nemici = 0 ;

    if ( chasers_enemies <= MAX_NEMICI_INS) {
        num_nemici = chasers_enemies ;
        num_nemici_ins = chasers_enemies ;
        for ( int i = 0 ; i < chasers_enemies ; i++ )
            nemici[i].setTipo( 'I' ) ;
    }

    posizionaNemici_v2() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    completato = false;
}


Level::Level(Map& m, int chasers_enemies, int random_enemies, int items) : map(m) {

    num_nemici = 0 ;

    if ( chasers_enemies <= MAX_NEMICI_INS) {
        num_nemici = chasers_enemies ;
        num_nemici_ins = chasers_enemies ;
        for ( int i = 0 ; i < chasers_enemies ; i++ )
            nemici[i].setTipo( 'I' ) ;
    }

    if (random_enemies <= MAX_NEMICI_RND) {
        num_nemici += random_enemies ;
        num_nemici_rdm = random_enemies ;
        for ( int i = num_nemici; i < chasers_enemies + random_enemies ; i++ ) {
            nemici[i].setTipo( 'R') ;
        }
    }

    posizionaNemici_v2() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    completato = false;
}


Level::Level(Map& m, int chasers_enemies, int random_enemies, int tank_enemies, int items) : map(m) {

    num_nemici = 0 ;

    if ( chasers_enemies <= MAX_NEMICI_INS) {
        num_nemici = chasers_enemies ;
        for ( int i = 0 ; i < chasers_enemies ; i++ )
            nemici[i].setTipo( 'I' ) ;
    }

    if (random_enemies <= MAX_NEMICI_RND) {
        num_nemici += random_enemies ;
        num_nemici_ins = chasers_enemies ;
        for ( int i = num_nemici; i < chasers_enemies + random_enemies ; i++ ) {
            nemici[i].setTipo( 'R') ;
        }
    }

    if (tank_enemies <= MAX_NEMICI_TANK) {
        num_nemici += tank_enemies ;
        num_nemici_tank = nemici_tank ;
        for ( int i = num_nemici; i < chasers_enemies + random_enemies + tank_enemies; i++ ) {
            nemici[i].setTipo( 'T') ;
        }
    }

    posizionaNemici_v2() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    completato = false;
}
//----------------------------------------------------------------------------------------------------------------------*/



Posizione Level::posizioneRandomValida() {

    Posizione temp = map.walkableRandomPosition( ) ;

    if ( !isThereAnEnemy( temp ))
        return temp ;

    return posizioneRandomValida() ;
}

/*chat suggerisce:
Posizione Level::posizioneRandomValida() {

    Posizione temp;

    do {
        temp = map.walkableRandomPosition();
    } while (isThereAnEnemy(temp));

    return
    temp;
}*/



void Level::posizionaNemici() {

    for ( int i = 0 ; i < num_nemici_ins ; i++ )
        nemici_inseguitore[i].setPosizione( posizioneRandomValida( ) ) ;

    for (int i = 0 ;  i < num_nemici_rnd ; i++ )
        nemici_random[i].setPosizione( posizioneRandomValida( ) ) ;
}


int Level::isThereARandomEnemy ( Posizione posizione ) {
    for (int i = 0 ; i < num_nemici_rnd ; i++ ) {
        if ( stessaPosizione(nemici_random[i].getPosizione( ), posizione ) && nemici_random[i].vivo( ) )
            return i ;
    }
    return -1 ;
}

int Level::isThereAnInsEnemy ( Posizione posizione ) {
    for (int i = 0 ; i < num_nemici_ins ; i++ ) {
        if ( stessaPosizione(nemici_inseguitore[i].getPosizione( ), posizione ) && nemici_inseguitore[i].vivo( ) )
            return i ;
    }
    return -1 ;
}



//IMPLEMENTAZIONE CON NEMICO--------------------------------------------------------------------------------------------
Posizione Level::posizioneRandomValida_v2() {
    Posizione temp = map.walkableRandomPosition( ) ;

    if ( !isThereAnEnemy_v2( temp ))
        return temp ;

    return posizioneRandomValida_v2() ;
}


void Level::posizionaNemici_v2( ) {
    for (int i = 0; i < num_nemici ; i++ )
        nemici[i].setPosizione( posizioneRandomValida()) ;
}


int Level::isThereAnEnemy_v2( Posizione posizione) {
    for (int i = 0 ; i < num_nemici ; i++) {
        if ( stessaPosizione( nemici[i].getPosizione(), posizione) && nemici[i].vivo( ))
            return i ;
    }
    return -1 ;
}
//----------------------------------------------------------------------------------------------------------------------

Map& Level::getMap(){
    return map;
}


void Level::updateEnemies(Personaggio& p){
    //Da scrivere
}

void Level::addItem(Item& i){
    //Da scrivere
}

void Level::updateItems(Item& i){
    //Da scrivere
}


bool Level::collisioneGiocatoreNemici (Giocatore& g ) {

    for ( int i = 0; i < num_nemici_ins ; i++ )
        if ( stessaPosizione( g.getPosizione(), nemici_inseguitore[i].getPosizione()) ) {
            g.diminuisciVita() ;
            return true ;
        }

    for ( int i = 0; i < num_nemici_rnd ; i++ )
        if ( stessaPosizione( g.getPosizione(), nemici_random[i].getPosizione()) ) {
            g.diminuisciVita() ;
            return true ;
        }

    return false ;
}


bool Level::collisioneGiocatoreNemici_v2(Giocatore &g) {
    for ( int i = 0 ; i < num_nemici ; i++ ) {
        if ( stessaPosizione( g.getPosizione(), nemici[i].getPosizione())) {
            g.diminuisciVita() ;
            return true ;
        }
    }
    return false ;
}


void Level::collisioneEsplosione(Giocatore& g ) {
    /*
 *prende la posizione della bomba
 *prende il raggio della bomba
 *calcola
 *controlla cella per cella
 *se una cella(x,y) == giocatore.posizione
 *      giocatore.diminuisci vita
 *se una cella(x,y) == nemico.posizione
 *      nemico.diminuisci vita
 *se una cella(x, y) == muro distruttibile
 *      muro.distruggi
    */
}


bool Level::collisioneEsplosioneGiocatore(Giocatore& g ) {
    //da scrivere
}



void Level::collisioneEsplosioneMuri_v1() {

    Posizione epicentro = b.getPosizione() ;

    Posizione nord = { epicentro.x, epicentro.y - b.getRaggio() - 1} ;
    Posizione sud = { epicentro.x, epicentro.y + b.getRaggio() + 1} ;
    Posizione est = { epicentro.x - b.getRaggio() - 1, epicentro.y} ;
    Posizione ovest = { epicentro.x + b.getRaggio() + 1, epicentro.y} ;

    Posizione controllata ;
    bool muro_distrutto = false ;


    controllata = { epicentro.x, epicentro.y - 1 } ;
    while ( !stessaPosizione(controllata, nord) && !map.isUnbreakableWall(controllata) && !muro_distrutto ) {
        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata) ;
        }
        controllata.y-- ;
    }

    controllata = { epicentro.x, epicentro.y + 1 } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, sud) && !map.isUnbreakableWall(controllata) && !muro_distrutto) {
        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1(controllata) ;
        }
        controllata.y++ ;
    }

    controllata = { epicentro.x - 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, est) && !map.isUnbreakableWall(controllata) && !muro_distrutto ) {
        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata ) ;
        }
        controllata.x-- ;
    }

    controllata = { epicentro.x + 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, ovest) && !map.isUnbreakableWall(controllata) && !muro_distrutto) {
        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata ) ;
        }
        controllata.x++ ;
    }
}

/*REVISIONE CON CHAT: ( void Level::collisioneEsplosioneMuri() )
I nomi est e ovest sembrano invertiti
eviterei est/ovest e userei nomi tipo limiteXNegativo, ecc.
I tuoi quattro while funzionano, ma hai praticamente quattro copie dello stesso algoritmo:
Dopo che hai implementato anche nemici e giocatore, possiamo fare una seconda versione più elegante usando una singola funzione del tipo concettuale:
controllaDirezione(dx, dy)
dove:
nord  -> dx = 0,  dy = -1
sud   -> dx = 0,  dy = +1
...

La stessa scansione delle quattro direzioni ti servirà anche per giocatore e nemici,
perché un nemico dietro a un muro non deve essere colpito.
Quindi eviterei di implementare le prossime collisioni completamente separate copiando di nuovo questi quattro while.

*/


void Level::collisioneEsplosioneMuriNemici_v1( ) {
    Posizione epicentro = b.getPosizione() ;

    Posizione nord = { epicentro.x, epicentro.y - b.getRaggio() - 1} ;
    Posizione sud = { epicentro.x, epicentro.y + b.getRaggio() + 1} ;
    Posizione est = { epicentro.x - b.getRaggio() - 1, epicentro.y} ;
    Posizione ovest = { epicentro.x + b.getRaggio() + 1, epicentro.y} ;

    Posizione controllata ;
    bool muro_distrutto = false ;
    int nemico_inseguitore_i ;
    int nemico_random_i ;


    //se i nemici possono andare sopra una bomba bisogna mettere il controllo epicentro

    controllata = { epicentro.x, epicentro.y - 1 } ;
    while ( !stessaPosizione(controllata, nord) && !map.isUnbreakableWall(controllata) && !muro_distrutto ) {
        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata) ;
        }

        nemico_inseguitore_i = isThereAnInsEnemy( controllata ) ;
        if ( nemico_inseguitore_i != -1 ) {
            //nemici_inseguitore[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        nemico_random_i = isThereARandomEnemy( controllata ) ;
        if (nemico_random_i != -1 ) {
            //nemici_random[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        controllata.y-- ;
    }


    controllata = { epicentro.x, epicentro.y + 1 } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, sud) && !map.isUnbreakableWall(controllata) && !muro_distrutto) {
        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1(controllata) ;
        }
        nemico_inseguitore_i = isThereAnInsEnemy( controllata ) ;
        if ( nemico_inseguitore_i != -1 ) {
            //nemici_inseguitore[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        nemico_random_i = isThereARandomEnemy( controllata ) ;
        if (nemico_random_i != -1 ) {
            //nemici_random[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        controllata.y++ ;
    }


    controllata = { epicentro.x - 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, est) && !map.isUnbreakableWall(controllata) && !muro_distrutto ) {
        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata ) ;
        }

        nemico_inseguitore_i = isThereAnInsEnemy( controllata ) ;
        if ( nemico_inseguitore_i != -1 && nemici_inseguitore[nemico_inseguitore_i].vivo( )) {
            //nemici_inseguitore[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        nemico_random_i = isThereARandomEnemy( controllata ) ;
        if (nemico_random_i != -1 && nemici_random[nemico_random_i].vivo( )) {
            //nemici_random[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        controllata.x-- ;
    }


    controllata = { epicentro.x + 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, ovest) && !map.isUnbreakableWall(controllata) && !muro_distrutto) {
        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata ) ;
        }

        nemico_inseguitore_i = isThereAnInsEnemy( controllata ) ;
        if ( nemico_inseguitore_i != -1 && nemici_inseguitore[nemico_inseguitore_i].vivo( )) {
            //nemici_inseguitore[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        nemico_random_i = isThereARandomEnemy( controllata ) ;
        if (nemico_random_i != -1 && nemici_random[nemico_random_i].vivo( )) {
            //nemici_random[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        controllata.x++ ;
    }
}


bool Level::collisioneEsplosioneMuriNemiciGiocatore_v1( Giocatore& g ) {

    Posizione epicentro = b.getPosizione() ;

    Posizione nord = { epicentro.x, epicentro.y - b.getRaggio() - 1} ;
    Posizione sud = { epicentro.x, epicentro.y + b.getRaggio() + 1} ;
    Posizione est = { epicentro.x - b.getRaggio() - 1, epicentro.y} ;
    Posizione ovest = { epicentro.x + b.getRaggio() + 1, epicentro.y} ;

    Posizione controllata = epicentro;
    bool muro_distrutto = false ;
    bool giocatore_colpito = false ;
    int nemico_inseguitore_i ;
    int nemico_random_i ;



    if (stessaPosizione(g.getPosizione(), epicentro)) {
        g.diminuisciVita();
        giocatore_colpito = true;
    }
    //se i nemici possono andare sopra una bomba bisogna mettere il controllo epicentro

    controllata = { epicentro.x, epicentro.y - 1 } ;
    while ( !stessaPosizione(controllata, nord) && !map.isUnbreakableWall(controllata) && !muro_distrutto ) {
        if ( stessaPosizione( g.getPosizione(), controllata )) {
            g.diminuisciVita() ;
            giocatore_colpito = true ;
        }


        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata) ;
        }

        nemico_inseguitore_i = isThereAnInsEnemy( controllata ) ;
        if ( nemico_inseguitore_i != -1 ) {
            //nemici_inseguitore[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        nemico_random_i = isThereARandomEnemy( controllata ) ;
        if (nemico_random_i != -1 ) {
            //nemici_random[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        controllata.y-- ;
    }


    controllata = { epicentro.x, epicentro.y + 1 } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, sud) && !map.isUnbreakableWall(controllata) && !muro_distrutto) {
        if ( stessaPosizione( g.getPosizione(), controllata )) {
            g.diminuisciVita() ;
            giocatore_colpito = true ;
        }

        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1(controllata) ;
        }
        nemico_inseguitore_i = isThereAnInsEnemy( controllata ) ;
        if ( nemico_inseguitore_i != -1 ) {
            //nemici_inseguitore[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        nemico_random_i = isThereARandomEnemy( controllata ) ;
        if (nemico_random_i != -1 ) {
            //nemici_random[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        controllata.y++ ;
    }


    controllata = { epicentro.x - 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, est) && !map.isUnbreakableWall(controllata) && !muro_distrutto ) {

        if ( stessaPosizione( g.getPosizione(), controllata )) {
            g.diminuisciVita() ;
            giocatore_colpito = true ;
        }

        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata ) ;
        }

        nemico_inseguitore_i = isThereAnInsEnemy( controllata ) ;
        if ( nemico_inseguitore_i != -1 && nemici_inseguitore[nemico_inseguitore_i].vivo( )) {
            //nemici_inseguitore[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        nemico_random_i = isThereARandomEnemy( controllata ) ;
        if (nemico_random_i != -1 && nemici_random[nemico_random_i].vivo( )) {
            //nemici_random[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        controllata.x-- ;
    }


    controllata = { epicentro.x + 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(controllata, ovest) && !map.isUnbreakableWall(controllata) && !muro_distrutto) {

        if ( stessaPosizione( g.getPosizione(), controllata )) {
            g.diminuisciVita() ;
            giocatore_colpito = true ;
        }

        if ( map.isBreakable(controllata) ) {
            map.breakWall(controllata ) ;
            muro_distrutto = true ;
            dropItem_v1( controllata ) ;
        }

        nemico_inseguitore_i = isThereAnInsEnemy( controllata ) ;
        if ( nemico_inseguitore_i != -1 && nemici_inseguitore[nemico_inseguitore_i].vivo( )) {
            //nemici_inseguitore[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        nemico_random_i = isThereARandomEnemy( controllata ) ;
        if (nemico_random_i != -1 && nemici_random[nemico_random_i].vivo( )) {
            //nemici_random[i].uccidi() //guarda meglio diminuisci vita o implementa uccidi
            dropItem_v1(controllata) ;
        }

        controllata.x++ ;
    }

    return giocatore_colpito ;
}


bool Level::collisioneEsplosioneMuriNemiciGiocatore_v2( Giocatore& g ) {
        Posizione epicentro = b.getPosizione() ;

    Posizione nord = { epicentro.x, epicentro.y - b.getRaggio() - 1} ;
    Posizione sud = { epicentro.x, epicentro.y + b.getRaggio() + 1} ;
    Posizione est = { epicentro.x - b.getRaggio() - 1, epicentro.y} ;
    Posizione ovest = { epicentro.x + b.getRaggio() + 1, epicentro.y} ;

    Posizione current = epicentro;
    bool muro_distrutto = false ;
    bool giocatore_colpito = false ;

    if (stessaPosizione(g.getPosizione(), epicentro)) {
        g.diminuisciVita();
        giocatore_colpito = true;
    }

    for ( int i = 0 ; i < num_nemici ; i++ ) {
        if ( isThereAnEnemy_v2( current )) {
            nemici[i].diminuisciVita( ) ;
            if ( !nemici[i].vivo( ))
                dropItem_v1( current ) ;
        }
    }

    //SU:
    current = { epicentro.x, epicentro.y - 1 } ;
    while ( !stessaPosizione(current, nord) && !map.isUnbreakableWall(current) && !muro_distrutto ) {
        if ( stessaPosizione( g.getPosizione(), current )) {
            g.diminuisciVita() ;
            giocatore_colpito = true ;
        }

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem_v1( current) ;
        }

        for ( int i = 0 ; i < num_nemici ; i++ ) {
            if ( isThereAnEnemy_v2( current )) {
                nemici[i].diminuisciVita( ) ;
                if ( !nemici[i].vivo( ))
                    dropItem_v1( current ) ;
            }
        }

        current.y-- ;
    }

    //GIU
    current = { epicentro.x, epicentro.y + 1 } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, sud) && !map.isUnbreakableWall(current) && !muro_distrutto) {
        if ( stessaPosizione( g.getPosizione(), current )) {
            g.diminuisciVita() ;
            giocatore_colpito = true ;
        }

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem_v1(current) ;
        }
        for ( int i = 0 ; i < num_nemici ; i++ ) {
            if ( isThereAnEnemy_v2( current )) {
                nemici[i].diminuisciVita( ) ;
                if ( !nemici[i].vivo( ))
                    dropItem_v1( current ) ;
            }
        }

        current.y++ ;
    }


    //SINISTRA
    current = { epicentro.x - 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, est) && !map.isUnbreakableWall(current) && !muro_distrutto ) {

        if ( stessaPosizione( g.getPosizione(), current )) {
            g.diminuisciVita() ;
            giocatore_colpito = true ;
        }

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem_v1( current ) ;
        }

        for ( int i = 0 ; i < num_nemici ; i++ ) {
            if ( isThereAnEnemy_v2( current )) {
                nemici[i].diminuisciVita( ) ;
                if ( !nemici[i].vivo( ))
                    dropItem_v1( current ) ;
            }
        }

        current.x-- ;
    }

    //DESTR
    current = { epicentro.x + 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, ovest) && !map.isUnbreakableWall(current) && !muro_distrutto) {

        if ( stessaPosizione( g.getPosizione(), current )) {
            g.diminuisciVita() ;
            giocatore_colpito = true ;
        }

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem_v1( current ) ;
        }

        for ( int i = 0 ; i < num_nemici ; i++ ) {
            if ( isThereAnEnemy_v2( current )) {
                nemici[i].diminuisciVita( ) ;
                if ( !nemici[i].vivo( ))
                    dropItem_v1( current ) ;
            }
        }

        current.x++ ;
    }

    return giocatore_colpito ;
}





void Level::collisioneEsplosioniNemici( ) {
    //da scrivere
}


void Level::raccoltaItem(Giocatore& g ) {
    for (int i = 0 ; i < next_item ; i++ )
        if ( stessaPosizione( g.getPosizione(), items[i].getPosizione()) && items[i].isAttivo() ) {
            items[i].raccogli() ;
            //applicaEffettoItem(items[i], b) ;
        }
}



void Level::dropItem_v1(Posizione posizione) {
    if ( next_item < num_items ) {
        int random = rand() % 5 ; //valutare a gioco creato se aumentare o diminuire

        if (random == 1) {
            items[next_item].setPosizione( posizione ) ;
            items[next_item].setTipoRandom( ) ;
            items[next_item].attiva( ) ;
            next_item++ ;
        }
    }
}


void Level::piazzaBomba(Giocatore& g) {
    b.setPosizione( g.getPosizione()) ;
    b.setTimer( 4 ) ; //forse inutile perche' il costruttore inizializza gia il timer a 4 e non viene aggiornato se la bomba non e' innescata
    b.innesca( ) ;
}

//IMPLEMENTAZIONE CON NEMICO--------------------------------------------------------------------------------------------
void Level::reset_v2() {


    // riporta tutti i nemici vivi
    for ( int i = 0 ; i < num_nemici; i++ ) {
        nemici[i].rianima( ) ;
    }
    // riposiziona tutti i nemici
    posizionaNemici_v2( ) ;

    next_item = 0 ;
    for (int i = 0 ; i < num_items ; i++ ) {
        items[i].disattiva() ;
        items[i].setPosizione (-1, -1) ;
    }

    // reset bomba
    b.esplodi( );
    b.setPosizione( -1, -1 ) ;

    completato = false;;
}