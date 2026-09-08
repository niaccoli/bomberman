//
// Created by andre on 07/08/2026.
//

#include  "Personaggio.hpp"
#include "Nemico.h"

#include "funzioni.h"

#include "Map.hpp"
#include <cstdlib>

Nemico::Nemico(): Personaggio(1, {-1, -1 }) {
    this -> tipo = ' ' ;
    this -> punti = 0 ;
}

Nemico::Nemico(char tipo): Personaggio(1, {-1, -1 }) {
    setTipo(tipo) ;
}

Nemico::Nemico (int vite, int x, int y, char tipo ): Personaggio( vite, x, y ) {
    setTipo(tipo) ;
}

Nemico::Nemico (int vite, Posizione posizione, char tipo ): Personaggio( vite, posizione ) {
    setTipo(tipo) ;

}

void Nemico::setTipo ( char tipo ) {
    if (tipo == 'I' ) {
        this -> tipo = tipo ;
        this -> punti = 200 ;
        setVite( 1 ) ;
    }
    else if (tipo == 'T') {
        this -> tipo = tipo ;
        this -> punti = 150 ;
        setVite( 2 ) ;
    }
    else if ( tipo == 'R') {
        this -> tipo = tipo ;
        this -> punti = 100 ;
        setVite( 1 ) ;
    }
    else {
        this -> tipo = ' ' ;
        this -> punti = 0 ;
    }
}

char Nemico::getTipo( ) const{
    return this -> tipo ;
}

int Nemico::getPunti ( ) {
    return this -> punti ;
}


int Nemico::percorsoBreve( Posizione player, Posizione n, Map& map, char& wasd) {
    if ( stessaPosizione( player, n))
        return 0 ;


    int min_sinistra = percorsoBreve( player, {n.x - 1, n.y}, map, wasd );
    int min_destra = percorsoBreve( player, {n.x + 1, n.y }, map , wasd);
    int min_su = percorsoBreve( player, {n.x, n.y - 1}, map , wasd);
    int min_giu = percorsoBreve( player, {n.x ,n.y + 1 }, map , wasd);

    int piuBreve = min(min_sinistra, min_destra, min_su, min_giu) ;

    if (piuBreve == min_sinistra)
        wasd = 'a' ;
    else if (piuBreve == min_destra)
        wasd = 'd' ;
	else if ( piuBreve == min_su )
        wasd == 'w' ;
    else
        wasd == 's' ;

    if ( !map.isWalkable( n ))
        return 100 + piuBreve;
    else
        return 1 + piuBreve ;
}

Posizione Nemico::nuovaPosizione ( Giocatore& g, Map& m ) {

    Posizione temp = posizione ;

    if (stessaPosizione(g.getPosizione(), getPosizione()))
        return temp;

    /*if ( tipo == 'I') {
        char movimento = ' ' ;
        percorsoBreve( g.getPosizione(), getPosizione(), m, movimento) ;
        if ( movimento == 'w') {
            temp.y -= 1 ;
        }
        if ( movimento == 'a') {
            temp.x -= 1 ;
        }
        if ( movimento == 's') {
            temp.y += 1 ;
        }
        if ( movimento == 'd') {
            temp.x += 1 ;
        }
        return temp ;

    }*/

    /*if ( tipo == 'I') {
        Posizione new_posizioni[4] ;
        double distanza_posizione_giocatore[4] ;
        int index_new_posizioni[4] ;

        for ( int i = 0 ; i < 4 ; i++ )
            new_posizioni[i] = posizione ;

        new_posizioni[0].x = posizione.x - 1 ;
        new_posizioni[1].y = posizione.y + 1 ;
        new_posizioni[2].x = posizione.x + 1 ;
        new_posizioni[3].y = posizione.y + 1 ;

        for ( int i = 0 ; i < 4 ; i++) {
            distanza_posizione_giocatore[i] = distanza( new_posizioni[i], g.getPosizione( ) ) ;
        }

        //riordino le distanze dalla piu' piccola alla piu' grande.
        //salvo in index_new_posizioni[4] gli indici delle new_posizioni dalla piu' piccola alla piu' grande

        for ( int i = 0 ; i < 3 ; i++ ) {
            int min = i ;
            for ( int j = i + 1 ; j < 4 ; j++ ) {
                if ( distanza_posizione_giocatore[i] < distanza_posizione_giocatore[min])
                    min = j ;
            }

            double dist_temp = distanza_posizione_giocatore[i] ;
            distanza_posizione_giocatore[i] = distanza_posizione_giocatore[min] ;
            distanza_posizione_giocatore[min] = dist_temp ;
            index_new_posizioni[i] = min ;
        }

        //piu la nuova posizione e' vicina al giocatore piu' e' probabile venga ritornata
        int random = rand() % 10 ;
        if ( random >= 0 && random < 5) {
            return new_posizioni[index_new_posizioni[0]] ;
        }
        if ( random >= 5 && random < 8) {
            return new_posizioni[index_new_posizioni[1]] ;
        }
        if ( random >= 8 && random < 9) {
            return new_posizioni[index_new_posizioni[2]] ;
        }
        if ( random >= 9 && random < 10) {
            return new_posizioni[index_new_posizioni[3]] ;
        }

    }*/

if (tipo == 'I') {

    int x_diff = g.getX() - getX();
    int y_diff = g.getY() - getY();


    Posizione possibili[4];


    if (abs(x_diff) > abs(y_diff)) {

            // 1. movimento orizzontale verso il giocatore
            if (x_diff > 0)
                possibili[0] = {temp.x + 1, temp.y};
            else
                possibili[0] = {temp.x - 1, temp.y};


            // 2. movimento verticale verso il giocatore
            if (y_diff > 0)
                possibili[1] = {temp.x, temp.y + 1};
            else if (y_diff < 0)
                possibili[1] = {temp.x, temp.y - 1};
            else
                possibili[1] = {temp.x, temp.y + 1};


            // 3. movimento orizzontale opposto al giocatore
            if (x_diff > 0)
                possibili[2] = {temp.x - 1, temp.y};
            else
                possibili[2] = {temp.x + 1, temp.y};


            // 4. movimento verticale opposto
            if (y_diff > 0)
                possibili[3] = {temp.x, temp.y - 1};
            else if (y_diff < 0)
                possibili[3] = {temp.x, temp.y + 1};
            else
                possibili[3] = {temp.x, temp.y - 1};
        }


        else {

            // 1. movimento verticale verso il giocatore
            if (y_diff > 0)
                possibili[0] = {temp.x, temp.y + 1};
            else
                possibili[0] = {temp.x, temp.y - 1};


            // 2. movimento orizzontale verso il giocatore
            if (x_diff > 0)
                possibili[1] = {temp.x + 1, temp.y};
            else if (x_diff < 0)
                possibili[1] = {temp.x - 1, temp.y};
            else
                possibili[1] = {temp.x + 1, temp.y};


            // 3. movimento verticale opposto al giocatore
            if (y_diff > 0)
                possibili[2] = {temp.x, temp.y - 1};
            else
                possibili[2] = {temp.x, temp.y + 1};


            // 4. movimento orizzontale opposto
            if (x_diff > 0)
                possibili[3] = {temp.x - 1, temp.y};
            else if (x_diff < 0)
                possibili[3] = {temp.x + 1, temp.y};
            else
                possibili[3] = {temp.x - 1, temp.y};
        }


        // Provo le quattro direzioni in ordine
        for (int i = 0; i < 4; i++) {

            if (m.isWalkable(possibili[i]))
                return possibili[i];
        }


        // Tutte e quattro le direzioni sono bloccate
        return temp;
    }

    if (tipo == 'R') {
            int random = rand() % 4 ;
            if ( random == 0 )
                temp.x -= 1 ;
            if ( random == 1 )
                temp.y += 1 ;
            if ( random == 2 )
                temp.x += 1 ;
            if ( random == 3 )
                temp.y -= 1 ;
            return temp ;
    }
    if ( tipo == 'T') {
            if ( rand() % 2 ) {
                int random = rand() % 4 ;
                if ( random == 0 )
                    temp.x -= 1 ;
                if ( random == 1 )
                    temp.y += 1 ;
                if ( random == 2 )
                    temp.x += 1 ;
                if ( random == 3 )
                    temp.y -= 1 ;
                return temp ;
            }

    }
    else
        return temp ;
    }

Posizione Nemico::nuovaPosizione_v3 (Map& m) {
    if (tipo == 'R' || tipo == 'I') {
        int random = rand() % 4 ;
        if ( random == 0 )
            posizione.x -= 1 ;
        if ( random == 1 )
            posizione.y += 1 ;
        if ( random == 2 )
            posizione.x += 1 ;
        if ( random == 3 )
            posizione.y -= 1 ;
    }
    else if ( tipo == 'T') {
        if ( rand() % 2 ) {
            int random = rand() % 4 ;
            if ( random == 0 )
                posizione.x -= 1 ;
            if ( random == 1 )
                posizione.y += 1 ;
            if ( random == 2 )
                posizione.x += 1 ;
            if ( random == 3 )
                posizione.y -= 1 ;
            
        }
    }
        return posizione ;
}

void Nemico::rianima( ) {
    if ( tipo == 'I' || tipo == 'R' )
        setVite( 1 ) ;
    if ( tipo == 'T' )
        setVite( 2 ) ;
}




