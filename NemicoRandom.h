#ifndef NEMICORANDOM_H
#define NEMICORANDOM_H

#include "Personaggio.hpp"
#include "Map.hpp"

class NemicoRandom : public Personaggio{
    public:
        NemicoRandom();
        void muovi( Map& m);

};


#endif