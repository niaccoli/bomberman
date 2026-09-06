//
// Created by andre on 06/09/2026.
//

#ifndef BOMBERMAN_CLASSIFICA_H
#define BOMBERMAN_CLASSIFICA_H


class Classifica {
protected:
    struct risultato {
        char nome[100] ;
        int punteggio ;
        risultato* next ;
    };
    typedef risultato* pris ;

    pris head ;

    pris aggiungiRisultato_aux (pris r, char nome[],int punteggio) ;

public :
    Classifica( ) ;

    void aggiungiRisultato(char nome[],int punteggio) ;
    //risultati ordinati per punteggio decrescente

    void caricaDaFile( ) ;

    void salvaSuFile( ) ;

    void mostraMigliori(int n) ;
};


#endif //BOMBERMAN_CLASSIFICA_H