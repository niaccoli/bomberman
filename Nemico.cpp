//
// Created by andre on 07/08/2026.
//

#include  "Personaggio.hpp"
#include "Nemico.h"
#include "Map.hpp"
#include <cstdlib>

Nemico::Nemico(): Personaggio(1, {-1, -1 }) {
    tipo = ' ' ; //valutare se assegnare il tipo rnd come predefinito o lasciare senza niente
}

Nemico::Nemico(char tipo): Personaggio(1, {-1, -1 }) {
    this -> tipo = tipo ;
    if ( tipo == 'T')
        Personaggio::setVite( 2 ) ;
}

Nemico::Nemico (int vite, int x, int y, char tipo ): Personaggio( vite, x, y ) {
    if ( tipo == 'T' )
        Personaggio::setVite( 2 ) ;
}

Nemico::Nemico (int vite, Posizione posizione, char tipo ): Personaggio( vite, posizione ) {
    if ( tipo == 'T' )
        Personaggio::setVite( 2 ) ;
}

void Nemico::setTipo ( char tipo ) {
    //ha senso usare else if o meglio if a cascata e non assegnare niente se il tipo non e' previsto?
    if (tipo == 'I' || tipo == 'R')
        this -> tipo = tipo ;
    else if (tipo == 'T') {
        this -> tipo = tipo ;
        setVite( 2 ) ;
    }
    else
        this -> tipo = ' ' ;
}

char Nemico::getTipo( ) {
    return this -> tipo ;
}

Posizione Nemico::nuovaPosizione ( Giocatore& g, Map& m ) {

    Posizione temp = posizione ;

    if ( tipo == 'I') {
        int x_diff = g.getX() - getX() ;
        int y_diff = g.getY() - getY() ;

        if ( abs(x_diff) > abs(y_diff)) {
            if ( x_diff > 0 )
                temp.x += 1 ;
            else
                temp.x -= 1 ;
        }
        else {
            if ( y_diff > 0 ) {
                temp.y -= 1 ;
            }
            else
                temp.y += 1 ;
        }
        return temp ;
    }
    else if (tipo == 'R') {
        int random = rand() % 3 ;
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
    else if ( tipo == 'T') {
        if ( rand() % 1 ) {
            int random = rand() % 3 ;
            if ( random == 0 )
                temp.x -= 1 ;
            if ( random == 1 )
                temp.y += 1 ;
            if ( random == 2 )
                temp.x += 1 ;
            if ( random == 3 )
                temp.y -= 1 ;
            
        }
        return temp ;
    }
    else
        return temp ;
}

Posizione Nemico::nuovaPosizione_v3 (Map& m) {
    if (tipo == 'R' || tipo == 'I') {
        int random = rand() % 3 ;
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
        if ( rand() % 1 ) {
            int random = rand() % 3 ;
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
    if ( tipo == 'R' )
        setVite( 2 ) ;
}




