#ifndef NEMICORANDOM_H
#define NEMICORANDOM_H

#include "Personaggio.hpp"
#include "Map.hpp"

class NemicoRandom : public Personaggio{
    public:
        NemicoRandom();
        void muovi( Map& m); //questa muovi utilizza la funzione mossaValida
        /*forse meglio creare una funzione nuovaPosizione che aggiorna due campi newX e newY, quindi nel main verificare
         *se è una posizione valida e chiamare Personaggio::muovi. */


};


#endif