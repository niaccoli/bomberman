//
// Created by andre on 07/08/2026.
//

#ifndef BOMBERMAN_NEMICO_H
#define BOMBERMAN_NEMICO_H

#include "Giocatore.h"
#include "Map.hpp"
#include "Personaggio.hpp"

class Map ; /* forward declaration
Nemico.h
↓ include
Map.hpp
↓ include
Nemico.h
void muovi(Giocatore& g, Map& m); può non aver ancora incontrato: class Map { ... };
*/


class Nemico : public Personaggio {
private:
    char tipo ; //'I' = Inseguitore, 'R' = random, 'T'=tank
    //int velocita ; //forse piuttosto che aggiungere un campo velocita' mi conviene aggiungere un randomico 1 su 2 per il
    //movimento del nemico tank in questo modo sembrera'  piu' lento

    public:
        Nemico () ;
        Nemico (char tipo) ;
        Nemico (int vite, int x, int y, char tipo ) ;
        Nemico (int vite, Posizione posizione, char tipo ) ;
        void setTipo ( char Tipo ) ;
        char getTipo ( ) ;
        Posizione nuovaPosizione (Giocatore& g, Map& m);
    //----------------------------------------------DA VALUTARE (guarda Level) -----------------------------------------
        Posizione nuovaPosizione_v3 (Map& m); //se il giocatore non e' presente nel livello i nemici inseguitori si comportano
    //come nemici random
    //-------------------------------------------------------------------------------------------------------------------
        void rianima( ) ;

};


#endif //BOMBERMAN_NEMICO_H