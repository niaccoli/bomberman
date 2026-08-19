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
    //void muovi ( Giocatore& g, Map& m ) ; //forse non serve includere la mappa
    //piu che altro forse conviene calcolare una posizione provvisoria,
    //quindi in level controllare se la posizione e' camminabile (Map::isWalkable)
    //e se non e' gia' occupata da un nemico (Level::iThereAnEnemy_v2)
    //e quindi muovere il personaggio in quella posizione
        Posizione nuovaPosizione ();
        void rianima( ) ;

};


#endif //BOMBERMAN_NEMICO_H