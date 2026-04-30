#ifndef NEMICOINSEGUITORE_H
#define NEMICOINSEGUITORE_H

#include "Personaggio.hpp"
#include "Map.hpp"
#include "Giocatore.h"

class NemicoInseguitore: public Personaggio {
    public:
        NemicoInseguitore();
        void muovi(Map& m,Giocatore& player);
};


#endif