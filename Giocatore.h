#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Personaggio.hpp"

class Giocatore : public Personaggio {
protected:
    bool invulnerabilita;
public:
    Giocatore();
    Giocatore(int vite, int x, int y);

    void InvulnerabilitaOn();
    void InvulnerabilitaOff();
    bool invulnerabile() const;
    void diminuisciVita();
    void diminuisciVita(int danno);
};


void muoviGiocatore(Giocatore& player, char input);



#endif //GIOCATORE_H