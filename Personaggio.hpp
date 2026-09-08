#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H
#include "Posizione.h"


class Personaggio {
    protected:
    // Numero di vite attuali del personaggio.
        int vite;

    // Posizione corrente del personaggio sulla mappa.
    // La posizione {-1, -1} può essere utilizzata per indicare
    // che il personaggio si trova fuori dalla mappa.
        Posizione posizione ;

    public:
    // Crea un personaggio con una vita
    // e posizione iniziale {-1, -1}.
        Personaggio();

    // Crea un personaggio con il numero di vite
    // e le coordinate specificate.
        Personaggio(int vite, int x, int y);

    // Crea un personaggio con il numero di vite
    // e la posizione specificata.
        Personaggio(int vite, Posizione posizione) ;

    // Imposta la coordinata x della posizione del personaggio.
        void setX(int x);

    // Imposta la coordinata y della posizione del personaggio.
        void setY(int y);

    // Imposta la posizione del personaggio.
        void setPosizione(Posizione posizione) ;

    // Restituisce la coordinata x della posizione del personaggio.
        int getX () const;

    // Restituisce la coordinata y della posizione del personaggio.
        int getY () const;

    // Restituisce la posizione corrente del personaggio.
        Posizione getPosizione() const;

    // Sposta il personaggio nelle coordinate specificate.
        void muovi(int newx, int newy);

    // Sposta il personaggio nella posizione specificata.
        void muovi(Posizione newp) ;

    // Imposta il numero di vite del personaggio.
        void setVite(int vite);

    // Aumenta di una unità il numero di vite del personaggio.
        void aumentaVita();

    // Diminuisce di una unità il numero di vite del personaggio.
        void diminuisciVita();

    // Diminuisce le vite del personaggio della quantità specificata.
        void diminuisciVita( int danno ) ;

    // Restituisce true se il personaggio possiede almeno una vita,
    // false altrimenti.
        bool vivo() const;

    // Restituisce il numero di vite attuali del personaggio.
        int getVite() const;
};

#endif

