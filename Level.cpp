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

    if ( items >= 0 && items <= MAX_ITEMS)
        num_items = items;

    else
        num_items = 0 ;

    completato = false;
}


Posizione Level::posizioneRandomValida() {



}



void Level::posizionaNemici() {

    for ( int i = 0 ; i < num_nemici_ins ; i++ )
        nemici_inseguitore[i].setPosizione( posizioneRandomValida( ) ) ;

    for (int i = 0 ;  i < num_nemici_rnd ; i++ )
        nemici_random[i].setPosizione( posizioneRandomValida( ) ) ;
}


int isThereAnEnemy ( Posizione posizione ) {

}

int isThereAInsEnemy ( Posizione posizione ) {

}


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

void reset() {
    // riporta tutti i nemici vivi
    // riposiziona tutti i nemici

    //current_item = 0;

    // disattiva tutti gli item
    // posizione (-1,-1)

    // reset bomba

    //completato = false;;
}

void Level::raccoltaItem(Giocatore& g ) {
    for (int i = 0 ; i < num_items ; i++ )
        if ( stessaPosizione( g.getPosizione(), items[i].getPosizione()) && items[i].isAttivo() ) {
            items[i].raccogli() ;
            applicaEffettoItem(items[i], b) ;
        }
}

bool Level::collisioneEsplosioneGiocatore(Giocatore& g ) {
    //da scrivere
}

void Level::collisioneEsplosioneMuri( ) {
    Posizione posizione_detonazione[5] ;
    posizione_detonazione[0] = b.getPosizione() ;

    posizione_detonazione[1].x = b.getX( ) - 1 ;
    posizione_detonazione[1].y = b.getY( ) ;

    posizione_detonazione[2].x = b.getX( ) + 1;
    posizione_detonazione[2].y = b.getY( ) ;

    posizione_detonazione[3].x = b.getX( ) ;
    posizione_detonazione[3].y = b.getY( ) + 1 ;

    posizione_detonazione[4].x = b.getX( ) ;
    posizione_detonazione[4].y = b.getY( ) - 1 ;

    for (int i = 0 ; i < 5 ; i++ ) {
        if ( map.isBreakable( posizione_detonazione[i] ) ) {
            map.breakWall( posizione_detonazione[i] ) ;
            dropItem_v1( posizione_detonazione[i] ) ;
        }
    }
}

void Level::collisioneEsplosioniNemici( ) {
    Posizione posizione_detonazione[5] ;
    posizione_detonazione[0] = b.getPosizione() ;

    posizione_detonazione[1].x = b.getX( ) - 1 ;
    posizione_detonazione[1].y = b.getY( ) ;

    posizione_detonazione[2].x = b.getX( ) + 1;
    posizione_detonazione[2].y = b.getY( ) ;

    posizione_detonazione[3].x = b.getX( ) ;
    posizione_detonazione[3].y = b.getY( ) + 1 ;

    posizione_detonazione[4].x = b.getX( ) ;
    posizione_detonazione[4].y = b.getY( ) - 1 ;

    for (int i = 0 ; i < 5 ; i++ ) {
        //
    }
}


void raccoltaItem(Giocatore& g ) {
    //da scrivere
    //valutare se in Level o Funzioni
}


/*void controllaCollisioni(Giocatore& g, Nemico& n[], Mappa& m, Bomba& b, Item i){
 *  collisioneGiocatoreNemici(g, n);
 *  if (giocatore.vivo()) //valutare se lasciare questo controllo, solo che senza la vita del giocatore potrebbe andare in negativo se dopo si prende anche una bomba
 *      if (b.innescata() && bomba.getTimer <= 0)
 *          collisioneEsplosione(g, n, m, b);
 *  if (giocatore.vivo())
 *      raccoltaItem(g, i, b)
 }*/


void Level::dropItem_v1(Posizione posizione) {
    if ( num_items >= 0 ) {
        int random = rand() % 5 ; //valutare a gioco creato se aumentare o diminuire

        if (random == 1) {
            items[num_items - 1].setPosizione( posizione ) ;
            items[num_items - 1].setTipoRandom( ) ;
            items[num_items - 1].attiva( ) ;
            num_items-- ;
        }
    }
}


void Level::piazzaBomba(Giocatore& g) {
    b.setPosizione( g.getPosizione()) ;
    b.setTimer( 4 ) ; //forse inutile perche' il costruttore inizializza gia il timer a 4 e non viene aggiornato se la bomba non e' innescata
    b.innesca( ) ;
}