#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Personaggio.hpp"

class Giocatore : public Personaggio {
protected:
    //bool invulnerabilita;
    //int tempoInvulnerabilita;
public:
    Giocatore();
    Giocatore(int vite, int x, int y);
    Giocatore(int vite, Posizione posizione) ;

    //void invulnerabilitaOn(int durata);
    //void invulnerabilitaOff();
    //bool invulnerabile() const;
    //void aggiornaInvulnerabilita();

    void diminuisciVita();
    void diminuisciVita(int danno);
};





#endif //GIOCATORE_H