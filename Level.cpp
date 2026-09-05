#include "Level.hpp"
#include "funzioni.h"
#include <cstdlib>
#include "Map.hpp"


Level::Level(Map& m, int random_enemies, int items) : map(m) {

    num_nemici = 0 ;

    if ( random_enemies <= MAX_NEMICI_RND && random_enemies >= 0) {
        num_nemici = random_enemies ;
        num_nemici_rnd = random_enemies ;
        for ( int i = 0 ; i < random_enemies ; i++ )
            nemici[i].setTipo( 'R' ) ;
    }
    else
        num_nemici_rnd = 0 ;

    num_nemici_ins = 0 ;
    num_nemici_tank = 0 ;

    posizionaNemici_v2() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    num_cella_esplosione = 0 ;

    completato = false;
}


Level::Level(Map& m, int chasers_enemies, int random_enemies, int items) : map(m) {

    
    num_nemici = 0 ;

    if ( chasers_enemies <= MAX_NEMICI_INS && chasers_enemies >= 0 ) {
        num_nemici = chasers_enemies ;
        num_nemici_ins = chasers_enemies ;
        for ( int i = 0 ; i < chasers_enemies ; i++ )
            nemici[i].setTipo( 'I' ) ;
    }
    else {
        num_nemici_ins = 0 ;
        chasers_enemies = 0 ;
    }

    if ( random_enemies <= MAX_NEMICI_RND && random_enemies >= 0 ) {
        num_nemici += random_enemies ;
        num_nemici_rnd = random_enemies ;
        for ( int i = num_nemici_ins ; i < chasers_enemies + random_enemies ; i++ ) {
            nemici[i].setTipo( 'R') ;
        }
    }
    else {
        num_nemici_rnd = 0 ;
        random_enemies = 0 ;
    }

    num_nemici_tank = 0 ;

    posizionaNemici_v2() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    num_cella_esplosione = 0 ;

    completato = false;
}


Level::Level(Map& m, int chasers_enemies, int random_enemies, int tank_enemies, int items) : map(m) {

    num_nemici = 0 ;


    if ( chasers_enemies <= MAX_NEMICI_INS && chasers_enemies >= 0) {
        num_nemici = chasers_enemies ;
        num_nemici_ins = chasers_enemies ;
        for ( int i = 0 ; i < chasers_enemies ; i++ )
            nemici[i].setTipo( 'I' ) ;
    }
    else {
        num_nemici_ins = 0 ;
        chasers_enemies = 0 ;
    }

    if (random_enemies <= MAX_NEMICI_RND && random_enemies >= 0 ) {
        num_nemici += random_enemies ;
        num_nemici_rnd = random_enemies ;
        for ( int i = num_nemici_ins; i < chasers_enemies + random_enemies ; i++ ) {
            nemici[i].setTipo( 'R') ;
        }
    }
    else {
        num_nemici_rnd = 0 ;
        random_enemies = 0 ;
    }

    if (tank_enemies <= MAX_NEMICI_TANK && tank_enemies >= 0) {
        num_nemici += tank_enemies ;
        num_nemici_tank = tank_enemies ;
        for ( int i = num_nemici_ins + num_nemici_rnd ; i < chasers_enemies + random_enemies + tank_enemies; i++ ) {
            nemici[i].setTipo( 'T') ;
        }
    }
    else {
        num_nemici_tank = 0 ;
        tank_enemies = 0 ;
    }

    posizionaNemici_v2() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    num_cella_esplosione = 0 ;

    completato = false;
}


Posizione Level::posizioneRandomValida_v2() {
    Posizione temp = map.walkableRandomPosition( ) ;


    if (( isThereAnEnemy_v2( temp ) == -1) && !map.isNearEntry(temp))
        return temp ;

    return posizioneRandomValida_v2() ;
}


/*
Posizione Level::posizioneRandomValida_v2() {
    Posizione temp;
    int tentativi = 0;

    do {
        temp = map.walkableRandomPosition();
        tentativi++;
    } while ((isThereAnEnemy_v2(temp) != -1) || map.isNearEntry(temp) && tentativi < 1000);

    return temp;
}*/




/*chat suggerisce:
Posizione Level::posizioneRandomValida() {

    Posizione temp;

    do {
        temp = map.walkableRandomPosition();
    } while (isThereAnEnemy(temp));

    return
    temp;
}*/



void Level::posizionaNemici_v2( ) {
    for (int i = 0; i < num_nemici ; i++ )
        nemici[i].setPosizione( posizioneRandomValida_v2()) ;
}


int Level::isThereAnEnemy_v2( Posizione posizione) {
    for (int i = 0 ; i < num_nemici ; i++) {
        if ( stessaPosizione( nemici[i].getPosizione(), posizione) && nemici[i].vivo( ))
            return i ;
    }
    return -1 ;
}

Map& Level::getMap(){
    return map;
}

void Level::stamp_map(Giocatore& g) {
    if ( num_cella_esplosione == 0 )
        map.stamp_map( g, nemici, num_nemici, items, num_items, b) ;
    else {
        map.stamp_map( g, nemici, num_nemici, items, num_items, b, cella_esplosione, num_cella_esplosione) ;

        num_cella_esplosione = 0 ;
    }
}

bool Level::isCompletato( ) {
    for ( int i = 0 ; i < num_nemici ; i++ ) {
        if (nemici[i].vivo( ))
            return false ;
    }
    completato = true ;
    return completato ;
}

/*
bool Level::updateLevel(Giocatore& g) {

    moveEnemies( g )  ;

    if ( collisioneGiocatoreNemici_v2( g )) {
        return true ;
    }

    if(active_explosion){
        visualize_explosion.diminuisci(1);

        if(visualize_explosion.scaduto()){
            active_explosion = false;

            num_cella_esplosione = 0;
        }
    }

    if ( b.aggiornaBomba( ) ) {
        bool giocatore_colpito = collisioneEsplosione( g ) ;

        active_explosion = true;
        visualize_explosion.attivaTimer(10);
        //collisione esplsione inizializza le cella_esplosione[]
        if ( giocatore_colpito)
            return true ;
    }

    //updateItem
    //quando gli item avranno una durata

    return false ;
} */

bool Level::updateEnemies(Giocatore& g) {

    moveEnemies( g )  ;

    if ( collisioneGiocatoreNemici_v2( g ))
        return true ;
    else
        return false ;
}

bool Level::aggiornaEsplosioni(Giocatore& g){

    if ( b.aggiornaBomba( ) )
        return ( collisioneEsplosione( g )) ;
    //collisione esplsione inizializza le cella_esplosione[]

    return false ;
}


void Level::moveEnemies(Giocatore& g){

    for ( int i = 0 ; i < num_nemici ; i++ ) {
        
        bool mosso = false ;
        int tentativo = 0 ;

        while ( !mosso && nemici[i].vivo() && tentativo < 10) {
            Posizione new_posizione = nemici[i].nuovaPosizione(g, map) ;
            if ( map.isWalkable( new_posizione ) && ( isThereAnEnemy_v2( new_posizione ) == -1 ) &&
                !(stessaPosizione( new_posizione, b.getPosizione()) && b.innescata())) {
                nemici[i].muovi( new_posizione ) ;
                mosso = true ;
            }
            tentativo++ ;
        }
    }
}


//Nuovo metodo post debug(creava un loop infinito)

/*void Level::updateEnemies(Giocatore& g){

    for ( int i = 0 ; i < num_nemici ; i++ ) {
        
        if ( !nemici[i].vivo() ) {
            continue;
        }

        bool mosso = false ;
        int tentativi = 0;

        while ( !mosso && tentativi < 10) {
            Posizione new_posizione = nemici[i].nuovaPosizione(g, map);
            
            if ( map.isWalkable( new_posizione) && !isThereAnEnemy_v2( new_posizione )) {
                nemici[i].muovi( new_posizione) ;
                mosso = true ;
            }

            tentativi++;
        }
    }
}*/



void Level::updateItems(){
    //Da scrivere quando gli items avranno una durata

}


/*bool Level::collisioneGiocatoreNemici_v2(Giocatore &g) {
    for ( int i = 0 ; i < num_nemici ; i++ ) {
        if ( stessaPosizione( g.getPosizione(), nemici[i].getPosizione()) && nemici[i].vivo()) {
            if (g.diminuisciVita() )
                return true;
        }
    }
    return false ;
}*/

bool Level::collisioneGiocatoreNemici_v2(Giocatore &g) {
    if ( isThereAnEnemy_v2(g.getPosizione()) != -1 ) {
        if (g.diminuisciVita() )
            return true;
    }
    return false ;
}


bool Level::collisioneEsplosione( Giocatore& g ) {
    Posizione epicentro = b.getPosizione() ;

    Posizione nord = { epicentro.x, epicentro.y - b.getRaggio() - 1} ;
    Posizione sud = { epicentro.x, epicentro.y + b.getRaggio() + 1} ;
    Posizione est = { epicentro.x - b.getRaggio() - 1, epicentro.y} ;
    Posizione ovest = { epicentro.x + b.getRaggio() + 1, epicentro.y} ;

    Posizione current = epicentro;
    bool muro_distrutto = false ;
    bool giocatore_colpito = false ;

    cella_esplosione[num_cella_esplosione] = current ;
    num_cella_esplosione++;


    if (stessaPosizione(g.getPosizione(), epicentro)) {
        if (g.diminuisciVita( ) )
            giocatore_colpito = true;
    }



    int index_enemy_in_current = isThereAnEnemy_v2( current ) ; //fondamentale sia perche' evita piu' chiamate
    //poi perche in
    // nemici[ isThereAnEnemy_v2( current )].diminuisciVita( );
    // se il nemico muore isThereAnEnemy_v2( current ) ritorna -1 quindi accedi fuori array
    //if ( !nemici[ index_enemy_in_current ].vivo( ))

    if ( index_enemy_in_current != -1 ) {
        nemici[ index_enemy_in_current ].diminuisciVita( ) ;
        if ( !nemici[ index_enemy_in_current ].vivo( ))
            dropItem( current ) ;
    }




    //SU:
    current = { epicentro.x, epicentro.y - 1 } ;
    while ( !stessaPosizione(current, nord) && !map.isUnbreakableWall(current) && !muro_distrutto ) {

        cella_esplosione[num_cella_esplosione] = current ;
        num_cella_esplosione++;

        if ( stessaPosizione( g.getPosizione(), current )) {
            if (g.diminuisciVita() )
                giocatore_colpito = true;
        }

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem( current) ;
        }

        index_enemy_in_current = isThereAnEnemy_v2( current ) ;

        if ( index_enemy_in_current != -1 ) {
            nemici[ index_enemy_in_current ].diminuisciVita( ) ;
            if ( !nemici[ index_enemy_in_current ].vivo( ))
                dropItem( current ) ;
        }

        current.y-- ;
    }

    //GIU
    current = { epicentro.x, epicentro.y + 1 } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, sud) && !map.isUnbreakableWall(current) && !muro_distrutto) {

        cella_esplosione[num_cella_esplosione] = current ;
        num_cella_esplosione++;

        if ( stessaPosizione( g.getPosizione(), current )) {
            if (g.diminuisciVita() )
                giocatore_colpito = true;
        }

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem(current) ;
        }


        index_enemy_in_current = isThereAnEnemy_v2( current ) ;

        if ( index_enemy_in_current != -1 ) {
            nemici[ index_enemy_in_current ].diminuisciVita( ) ;
            if ( !nemici[ index_enemy_in_current ].vivo( ))
                dropItem( current ) ;
        }

        current.y++ ;
    }


    //SINISTRA
    current = { epicentro.x - 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, est) && !map.isUnbreakableWall(current) && !muro_distrutto ) {

        cella_esplosione[num_cella_esplosione] = current ;
        num_cella_esplosione++;

        if ( stessaPosizione( g.getPosizione(), current )) {
            if (g.diminuisciVita() )
                giocatore_colpito = true;
        }

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem( current ) ;
        }


        index_enemy_in_current = isThereAnEnemy_v2( current ) ;

        if ( index_enemy_in_current != -1 ) {
            nemici[ index_enemy_in_current ].diminuisciVita( ) ;
            if ( !nemici[ index_enemy_in_current ].vivo( ))
                dropItem( current ) ;
        }

        current.x-- ;
    }

    //DESTRA
    current = { epicentro.x + 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, ovest) && !map.isUnbreakableWall(current) && !muro_distrutto) {

        cella_esplosione[num_cella_esplosione] = current ;
        num_cella_esplosione++;

        if ( stessaPosizione( g.getPosizione(), current )) {
            if (g.diminuisciVita() )
                giocatore_colpito = true;
        }

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem( current ) ;
        }


        index_enemy_in_current = isThereAnEnemy_v2( current ) ;

        if ( index_enemy_in_current != -1 ) {
            nemici[ index_enemy_in_current ].diminuisciVita( ) ;
            if ( !nemici[ index_enemy_in_current ].vivo( ))
                dropItem( current ) ;
        }

        current.x++ ;
    }

    return giocatore_colpito ;
}





char Level::raccoltaItem(Giocatore& g ) {
    for (int i = 0 ; i < next_item ; i++ )

        if ( stessaPosizione( g.getPosizione(), items[i].getPosizione()) && items[i].isAttivo() ) {
            items[i].raccogli( ) ;
            return items[i].getTipo() ;
        }

    return (' ') ;
}



void Level::dropItem(Posizione posizione) {
    if ( next_item < num_items ) {
        int random = rand() % 5 ; //valutare a gioco creato se aumentare o diminuire

        if (random == 1) {
            items[next_item].setPosizione( posizione ) ;
            items[next_item].setTipoRandom_v2( ) ;
            items[next_item].attiva( ) ;
            next_item++ ;
        }
    }
}


void Level::piazzaBomba(Giocatore& g) {
    if ( !b.innescata()) {
        b.setPosizione( g.getPosizione()) ;
        b.innesca() ;
    }
}

void Level::reset_v1() {
    b.esplodi( );
    b.disattivaPotenziamenti() ;
    b.setPosizione( -1, -1 ) ;
}


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
    b.disattivaPotenziamenti() ;
    b.setPosizione( -1, -1 ) ;

    completato = false;

}


void Level::aggiornaPotenziamenti() {
    b.aggiornaPotenziamenti( ) ;
}

void Level::applicaEffetto(char tipo ) {
    if ( tipo == 'D') {
        b.attivaBoostDanno( ) ;
    }
    if ( tipo == 'R') {
        b.attivaBoostRaggio( );
    }
    if ( tipo == 'T') {
        b.attivaBoostTimer( ) ;
    }
}

//---------------------------------------------------DA VALUTARE-------------------------------------------------------


void Level::updateLevel_v3() {

    updateEnemies_v3( ) ;

    if (b.aggiornaBomba( ) )
        collisioneEplosione_v3() ;

    //updateItems( ) ;
}

void Level::updateEnemies_v3( ) {
    for ( int i = 0 ; i < num_nemici ; i++ ) {
        bool mosso = false ;
        while ( !mosso && nemici[i].vivo()) {
            Posizione new_posizione = nemici[i].nuovaPosizione_v3( map ) ;
            if ( map.isWalkable( new_posizione) && !isThereAnEnemy_v2( new_posizione )) {
                nemici[i].muovi( new_posizione) ;
                mosso = true ;
            }
        }
    }
}



void Level::collisioneEplosione_v3( ) {
    Posizione epicentro = b.getPosizione() ;

    Posizione nord = { epicentro.x, epicentro.y - b.getRaggio() - 1} ;
    Posizione sud = { epicentro.x, epicentro.y + b.getRaggio() + 1} ;
    Posizione est = { epicentro.x - b.getRaggio() - 1, epicentro.y} ;
    Posizione ovest = { epicentro.x + b.getRaggio() + 1, epicentro.y} ;

    Posizione current = epicentro;
    bool muro_distrutto = false ;

    for ( int i = 0 ; i < num_nemici ; i++ ) {
        if ( isThereAnEnemy_v2( current )) {
            nemici[i].diminuisciVita( ) ;
            if ( !nemici[i].vivo( ))
                dropItem( current ) ;
        }
    }

    //SU:
    current = { epicentro.x, epicentro.y - 1 } ;
    while ( !stessaPosizione(current, nord) && !map.isUnbreakableWall(current) && !muro_distrutto ) {

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem( current) ;
        }

        for ( int i = 0 ; i < num_nemici ; i++ ) {
            if ( isThereAnEnemy_v2( current )) {
                nemici[i].diminuisciVita( ) ;
                if ( !nemici[i].vivo( ))
                    dropItem( current ) ;
            }
        }

        current.y-- ;
    }

    //GIU
    current = { epicentro.x, epicentro.y + 1 } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, sud) && !map.isUnbreakableWall(current) && !muro_distrutto) {

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem(current) ;
        }
        for ( int i = 0 ; i < num_nemici ; i++ ) {
            if ( isThereAnEnemy_v2( current )) {
                nemici[i].diminuisciVita( ) ;
                if ( !nemici[i].vivo( ))
                    dropItem( current ) ;
            }
        }

        current.y++ ;
    }


    //SINISTRA
    current = { epicentro.x - 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, est) && !map.isUnbreakableWall(current) && !muro_distrutto ) {

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem( current ) ;
        }

        for ( int i = 0 ; i < num_nemici ; i++ ) {
            if ( isThereAnEnemy_v2( current )) {
                nemici[i].diminuisciVita( ) ;
                if ( !nemici[i].vivo( ))
                    dropItem( current ) ;
            }
        }

        current.x-- ;
    }

    //DESTRA
    current = { epicentro.x + 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, ovest) && !map.isUnbreakableWall(current) && !muro_distrutto) {

        if ( map.isBreakable(current) ) {
            map.breakWall(current ) ;
            muro_distrutto = true ;
            dropItem( current ) ;
        }

        for ( int i = 0 ; i < num_nemici ; i++ ) {
            if ( isThereAnEnemy_v2( current )) {
                nemici[i].diminuisciVita( ) ;
                if ( !nemici[i].vivo( ))
                    dropItem( current ) ;
            }
        }

        current.x++ ;
    }
}


