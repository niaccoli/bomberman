//
// Created by andre on 07/08/2026.
//

#include  "Personaggio.hpp"
#include "Nemico.h"
#include "Map.hpp"

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
    if (tipo == 'I')
        this -> tipo = tipo ;
    else if (tipo == 'R')
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

/*void Nemico::muovi ( Giocatore& g, Map& m ) { //meglio degli else if?
    if ( tipo == 'I') {
        //
    }
    if (tipo == 'R') {
        //
    }
    if ( tipo == 'T') {
        //
    }
}*/

void Nemico::rianima( ) {
    if ( tipo == 'I' || tipo == 'R' )
        setVite( 1 ) ;
    if ( tipo == 'R' )
        setVite( 2 ) ;
}




