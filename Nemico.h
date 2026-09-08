//
// Created by andre on 07/08/2026.
//

#ifndef BOMBERMAN_NEMICO_H
#define BOMBERMAN_NEMICO_H

#include "Giocatore.h"
#include "Mappa.hpp"
#include "Personaggio.hpp"

class Mappa ; /* forward declaration
Nemico.h
↓ include
Mappa.hpp
↓ include
Nemico.h
void muovi(Giocatore& g, Mappa& m); può non aver ancora incontrato: class Mappa { ... };
*/


class Nemico : public Personaggio {
private:
    char tipo ; //'I' = Inseguitore, 'R' = random, 'T'=tank
    //int velocita ; //forse piuttosto che aggiungere un campo velocita' mi conviene aggiungere un randomico 1 su 2 per il
    //movimento del nemico tank in questo modo sembrera'  piu' lento
    int percorsoBreve( Posizione player, Posizione nemico, Mappa& mappa, char& wasd) ;
    int punti ;

    public:
        Nemico () ;
        Nemico (char tipo) ;
        Nemico (int vite, int x, int y, char tipo ) ;
        Nemico (int vite, Posizione posizione, char tipo ) ;
        void setTipo ( char tipo ) ;
        char getTipo ( ) const;
        int getPunti ( ) ;
        void nuovaPosizioneInseguitore (Giocatore& g, Posizione possibili[4]) const;
        Posizione nuovaPosizioneCasuale (Giocatore& g) const;
    //----------------------------------------------DA VALUTARE (guarda Livello) -----------------------------------------
        Posizione nuovaPosizione_v3 (Mappa& m); //se il giocatore non e' presente nel livello i nemici inseguitori si comportano
    //come nemici random
    //-------------------------------------------------------------------------------------------------------------------
        void rianima( ) ;

};


#endif //BOMBERMAN_NEMICO_H