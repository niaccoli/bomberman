#include  "Personaggio.hpp"
#include "Nemico.hpp"
#include "funzioni.hpp"
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




void Nemico::nuovaPosizioneInseguitore(Giocatore& g, Posizione possibili[4]) const{

    int x_diff = g.getX() - getX();
    int y_diff = g.getY() - getY();

    if (abs(x_diff) > abs(y_diff)) {

        // 1. orizzontale verso il giocatore
        if (x_diff > 0)
            possibili[0] = {posizione.x + 1, posizione.y};
        else
            possibili[0] = {posizione.x - 1, posizione.y};


        // 2. verticale verso il giocatore
        if (y_diff > 0)
            possibili[1] = {posizione.x, posizione.y + 1};
        else if (y_diff < 0)
            possibili[1] = {posizione.x, posizione.y - 1};
        else
            possibili[1] = {posizione.x, posizione.y + 1};


        // 3. orizzontale opposto
        if (x_diff > 0)
            possibili[2] = {posizione.x - 1, posizione.y};
        else
            possibili[2] = {posizione.x + 1, posizione.y};


        // 4. verticale opposto
        if (y_diff > 0)
            possibili[3] = {posizione.x, posizione.y - 1};
        else if (y_diff < 0)
            possibili[3] = {posizione.x, posizione.y + 1};
        else
            possibili[3] = {posizione.x, posizione.y - 1};
    }

    else {

        // 1. verticale verso il giocatore
        if (y_diff > 0)
            possibili[0] = {posizione.x, posizione.y + 1};
        else
            possibili[0] = {posizione.x, posizione.y - 1};


        // 2. orizzontale verso il giocatore
        if (x_diff > 0)
            possibili[1] = {posizione.x + 1, posizione.y};
        else if (x_diff < 0)
            possibili[1] = {posizione.x - 1, posizione.y};
        else
            possibili[1] = {posizione.x + 1, posizione.y};


        // 3. verticale opposto
        if (y_diff > 0)
            possibili[2] = {posizione.x, posizione.y - 1};
        else
            possibili[2] = {posizione.x, posizione.y + 1};


        // 4. orizzontale opposto
        if (x_diff > 0)
            possibili[3] = {posizione.x - 1, posizione.y};
        else if (x_diff < 0)
            possibili[3] = {posizione.x + 1, posizione.y};
        else
            possibili[3] = {posizione.x - 1, posizione.y};
    }
}

Posizione Nemico::nuovaPosizioneCasuale(Giocatore& g ) const{

    Posizione temp = posizione;

    if (stessaPosizione(g.getPosizione(), getPosizione()))
        return temp;


    if (tipo == 'R') {

        int random = rand() % 4;

        if (random == 0)
            temp.x -= 1;

        if (random == 1)
            temp.y += 1;

        if (random == 2)
            temp.x += 1;

        if (random == 3)
            temp.y -= 1;

        return temp;
    }

    else if (tipo == 'T') {

        if (rand() % 2) {

            int random = rand() % 4;

            if (random == 0)
                temp.x -= 1;

            if (random == 1)
                temp.y += 1;

            if (random == 2)
                temp.x += 1;

            if (random == 3)
                temp.y -= 1;
        }

        return temp;
    }

    return temp;
}


void Nemico::rianima( ) {
    if ( tipo == 'I' || tipo == 'R' )
        setVite( 1 ) ;
    if ( tipo == 'T' )
        setVite( 2 ) ;
}




