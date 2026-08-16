#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H
#include "Posizione.h"


class Personaggio {
    protected:
        int vite;
        /*int x;
        int y;*/
        Posizione posizione ;

    public:
        Personaggio();
        Personaggio(int vite, int x, int y);
        Personaggio(int vite, Posizione posizione) ;

        void setX(int x);
        void setY(int y);
        void setPosizione(Posizione posizione) ;
        int getX () const;
        int getY () const;
        Posizione getPosizione() const;
        void muovi(int newx, int newy);
        void muovi(Posizione newp) ;


        void setVite(int vite);
        void aumentaVita();
        void diminuisciVita();
        bool vivo() const;
        int getVite() const;
};

#endif

