//
// Created by andre on 06/09/2026.
//

#include "Classifica.h"
#include "cstring"

Classifica::Classifica( ) {
    head = nullptr ;
}

Classifica::pris Classifica::aggiungiRisultato_aux (pris r, char nome[],int punteggio) {
    if ( r == nullptr ) {
        pris temp = new risultato ;
        temp -> punteggio = punteggio ;
        strncpy( temp -> nome, nome, 99) ;
        temp -> nome[99] = '\0';
        temp -> next = nullptr ;
        return temp ;
    }

    if ( punteggio >= r -> punteggio ) {
        pris temp = new risultato ;
        temp -> punteggio = punteggio ;
        strncpy( temp -> nome, nome, 99) ;
        temp -> nome[99] = '\0';
        temp -> next = r ;
        return temp ;
    }

    else {
        r -> next = aggiungiRisultato_aux(r -> next, nome, punteggio ) ;
        return r ;
    }
}


void Classifica::aggiungiRisultato(char nome[], int punteggio) {
    head = aggiungiRisultato_aux( head, nome, punteggio ) ;
}

