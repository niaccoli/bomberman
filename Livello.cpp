#include "Livello.hpp"
#include "funzioni.hpp"
#include <cstdlib>
#include "Mappa.hpp"


Livello::Livello(Mappa& m, int random_enemies, int items) : mappa(m) {

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

    posizionaNemici() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    num_cella_esplosione = 0 ;

    completato = false;
}


Livello::Livello(Mappa& m, int chasers_enemies, int random_enemies, int items) : mappa(m) {

    
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

    posizionaNemici() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    num_cella_esplosione = 0 ;

    completato = false;
}


Livello::Livello(Mappa& m, int chasers_enemies, int random_enemies, int tank_enemies, int items) : mappa(m) {

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

    posizionaNemici() ;

    if ( items >= 0 && items <= MAX_ITEMS) {
        num_items = items;
    }
    else
        num_items = 0 ;
    next_item = 0 ;

    num_cella_esplosione = 0 ;

    completato = false;
}

Livello::~Livello() {
    delete &(this->mappa);
}


Posizione Livello::posizioneRandomValida() {
    Posizione temp = mappa.posizioneCamminabileRandom( ) ;


    if (( isThereAnEnemy( temp ) == -1) && !mappa.isVicinoEntrata(temp) && mappa.isCircondataDaMuri(temp))
        return temp ;

    return posizioneRandomValida() ;
}


Bomba& Livello::getBomb(){
    return this->b;
}


void Livello::posizionaNemici( ) {
    for (int i = 0; i < num_nemici ; i++ )
        nemici[i].setPosizione( posizioneRandomValida()) ;
}


int Livello::isThereAnEnemy( Posizione posizione) {
    for (int i = 0 ; i < num_nemici ; i++) {
        if ( stessaPosizione( nemici[i].getPosizione(), posizione) && nemici[i].vivo( ))
            return i ;
    }
    return -1 ;
}

Mappa& Livello::getMap(){
    return mappa;
}

void Livello::stampaMappa(Giocatore& g, int timer_gioco) {
    if ( num_cella_esplosione == 0 )
        mappa.stampaMappa( g, nemici, num_nemici, items, num_items, b, timer_gioco) ;
    else {
        mappa.stampaMappa( g, nemici, num_nemici, items, num_items, b, cella_esplosione, num_cella_esplosione, timer_gioco) ;

        num_cella_esplosione = 0 ;
    }
}

bool Livello::isCompletato( ) {
    for ( int i = 0 ; i < num_nemici ; i++ ) {
        if (nemici[i].vivo( ))
            return false ;
    }
    completato = true ;
    return completato ;
}

bool Livello::aggiornaEsplosioni(Giocatore& g ,int durata ) {
    if ( b.aggiornaBomba( durata ) )
        return ( collisioneEsplosione( g )) ;
    //collisione esplsione inizializza le cella_esplosione[]

    return false ;
}


void Livello::muoviNemici(Giocatore& g) {

    for (int i = 0; i < num_nemici; i++) {

        if (nemici[i].vivo()) {

            // INSEGUITORE
            if (nemici[i].getTipo() == 'I') {


                if (!stessaPosizione(nemici[i].getPosizione(), g.getPosizione())) {

                    Posizione possibili[4];

                    nemici[i].nuovaPosizioneInseguitore(g, possibili);

                    bool mosso = false;
                    int j = 0;

                    while (j < 4 && !mosso) {

                bool cellaLibera =
                    mappa.isCamminabile(possibili[j]) &&
                    isThereAnEnemy(possibili[j]) == -1 &&
                    !(stessaPosizione(possibili[j], b.getPosizione()) &&
                      b.innescata());

                        if (cellaLibera) {
                            nemici[i].muovi(possibili[j]);
                            mosso = true;
                        }

                        j++;
                    }
                }
            }

            // RANDOM E TANK
            else {

                bool mosso = false;
                int tentativo = 0;

                while (!mosso && tentativo < 10) {

                    Posizione nuova = nemici[i].nuovaPosizioneCasuale(g);

                    // Per il nemico tank: può decidere di rimanere fermo
                    if (stessaPosizione(nuova, nemici[i].getPosizione())) {
                        mosso = true;
                    }


                if (mappa.isCamminabile(nuova) &&
                    isThereAnEnemy(nuova) == -1 &&
                    !(stessaPosizione(nuova, b.getPosizione()) &&
                      b.innescata())) {

                        nemici[i].muovi(nuova);
                        mosso = true;
                    }

                    tentativo++;
                }
            }
        }
    }
}


bool Livello::collisioneGiocatoreNemici(Giocatore &g) {

    if ( isThereAnEnemy(g.getPosizione()) != -1 ) {
        if (g.diminuisciVita() )
            return true;
    }
    return false ;
}


bool Livello::collisioneEsplosione( Giocatore& g ) {
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
        if (g.diminuisciVita( b.getDanno()) )
            giocatore_colpito = true;
    }



    int index_enemy_in_current = isThereAnEnemy( current ) ;
    if ( index_enemy_in_current != -1 ) {
        nemici[ index_enemy_in_current ].diminuisciVita( b.getDanno() ) ;
        if ( !nemici[ index_enemy_in_current ].vivo( )) {
            dropItem( current ) ;
            g.aumentaPunteggio( nemici[index_enemy_in_current].getPunti()) ;
        }
    }




    //SU:
    current = { epicentro.x, epicentro.y - 1 } ;
    while ( !stessaPosizione(current, nord) && !mappa.isMuroIndistruttibile(current) && !muro_distrutto ) {

        cella_esplosione[num_cella_esplosione] = current ;
        num_cella_esplosione++;

        if ( stessaPosizione( g.getPosizione(), current )) {
            if (g.diminuisciVita( b.getDanno() ) )
                giocatore_colpito = true;
        }

        if ( mappa.isDistruttibile(current) ) {
            mappa.distruggiMuro(current ) ;
            muro_distrutto = true ;
            dropItem( current) ;
        }

        index_enemy_in_current = isThereAnEnemy( current ) ;

        if ( index_enemy_in_current != -1 ) {
            nemici[ index_enemy_in_current ].diminuisciVita( b.getDanno( )) ;
            if ( !nemici[ index_enemy_in_current ].vivo( )) {
                dropItem( current ) ;
                g.aumentaPunteggio( nemici[index_enemy_in_current].getPunti()) ;
            }
        }

        current.y-- ;
    }

    //GIU
    current = { epicentro.x, epicentro.y + 1 } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, sud) && !mappa.isMuroIndistruttibile(current) && !muro_distrutto) {

        cella_esplosione[num_cella_esplosione] = current ;
        num_cella_esplosione++;

        if ( stessaPosizione( g.getPosizione(), current )) {
            if (g.diminuisciVita(b.getDanno()) )
                giocatore_colpito = true;
        }

        if ( mappa.isDistruttibile(current) ) {
            mappa.distruggiMuro(current ) ;
            muro_distrutto = true ;
            dropItem(current) ;
        }


        index_enemy_in_current = isThereAnEnemy( current ) ;

        if ( index_enemy_in_current != -1 ) {
            nemici[ index_enemy_in_current ].diminuisciVita( b.getDanno() ) ;
            if ( !nemici[ index_enemy_in_current ].vivo( )) {
                dropItem( current ) ;
                g.aumentaPunteggio( nemici[index_enemy_in_current].getPunti()) ;
            }
        }

        current.y++ ;
    }


    //SINISTRA
    current = { epicentro.x - 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, est) && !mappa.isMuroIndistruttibile(current) && !muro_distrutto ) {

        cella_esplosione[num_cella_esplosione] = current ;
        num_cella_esplosione++;

        if ( stessaPosizione( g.getPosizione(), current )) {
            if (g.diminuisciVita(b.getDanno()) )
                giocatore_colpito = true;
        }

        if ( mappa.isDistruttibile(current) ) {
            mappa.distruggiMuro(current ) ;
            muro_distrutto = true ;
            dropItem( current ) ;
        }


        index_enemy_in_current = isThereAnEnemy( current ) ;

        if ( index_enemy_in_current != -1 ) {
            nemici[ index_enemy_in_current ].diminuisciVita(b.getDanno() ) ;
            if ( !nemici[ index_enemy_in_current ].vivo( )) {
                dropItem( current ) ;
                g.aumentaPunteggio( nemici[index_enemy_in_current].getPunti()) ;
            }
        }

        current.x-- ;
    }

    //DESTRA
    current = { epicentro.x + 1, epicentro.y } ;
    muro_distrutto = false ;
    while ( !stessaPosizione(current, ovest) && !mappa.isMuroIndistruttibile(current) && !muro_distrutto) {

        cella_esplosione[num_cella_esplosione] = current ;
        num_cella_esplosione++;

        if ( stessaPosizione( g.getPosizione(), current )) {
            if (g.diminuisciVita(b.getDanno()) )
                giocatore_colpito = true;
        }

        if ( mappa.isDistruttibile(current) ) {
            mappa.distruggiMuro(current ) ;
            muro_distrutto = true ;
            dropItem( current ) ;
        }


        index_enemy_in_current = isThereAnEnemy( current ) ;

        if ( index_enemy_in_current != -1 ) {
            nemici[ index_enemy_in_current ].diminuisciVita(b.getDanno() ) ;
            if ( !nemici[ index_enemy_in_current ].vivo( )) {
                dropItem( current ) ;
                g.aumentaPunteggio( nemici[index_enemy_in_current].getPunti()) ;
            }
        }

        current.x++ ;
    }

    return giocatore_colpito ;
}





char Livello::raccoltaItem(Giocatore& g ) {
    for (int i = 0 ; i < next_item ; i++ )

        if ( stessaPosizione( g.getPosizione(), items[i].getPosizione()) && items[i].isAttivo() ) {
            items[i].raccogli( ) ;
            return items[i].getTipo() ;
        }

    return (' ') ;
}



void Livello::dropItem(Posizione posizione) {
    if ( next_item < num_items ) {
        int random = rand() % 5 ;

        if (random == 1) {
            items[next_item].setPosizione( posizione ) ;
            items[next_item].setTipoRandom( ) ;
            items[next_item].attiva( ) ;
            next_item++ ;
        }
    }
}


void Livello::piazzaBomba(Giocatore& g) {
    if ( !b.innescata()) {
        b.setPosizione( g.getPosizione()) ;
        b.innesca() ;
    }
}

void Livello::resetBombeEPotenziamenti() {
    b.esplodi( );
    b.disattivaPotenziamenti() ;
    b.setPosizione( -1, -1 ) ;
}



void Livello::reset_v3( ) {

    posizionaNemici() ;

    resetBombeEPotenziamenti() ;
}



void Livello::aggiornaPotenziamenti(int durata ) {
    b.aggiornaPotenziamenti(durata) ;
}

void Livello::applicaEffetto(char tipo ) {
    if ( tipo == 'D') {
        b.attivaPotenziamentoDanno( ) ;
    }
    if ( tipo == 'R') {
        b.attivaPotenziamentoRaggio( );
    }
    if ( tipo == 'T') {
        b.attivaPotenziamentoTimer( ) ;
    }
}


