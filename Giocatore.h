#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Personaggio.hpp"

class Giocatore : public Personaggio {
protected:
    const int defaultTimerInvulnerabilitaMs = 10000 ;

    bool invulnerabilita;
    int tempoInvulnerabilita;
public:
    Giocatore();
    Giocatore(int vite, int x, int y);
    Giocatore(int vite, Posizione posizione) ;

    void invulnerabilitaOn (  ); //attiva invulnerabilita

    void invulnerabilitaOn(int durata);

    void invulnerabilitaOff( ); //distattiva invulnerabilita' e reimposta il tempo invulnerabilita' a zero

    bool invulnerabile( ) const; //ritorna true se invulnerabilita attiva, false altrimenti

    void aggiornaInvulnerabilita(int durata );

    bool diminuisciVita();
    // Ridefinisco diminuisciVita() in Giocatore perché il giocatore può avere
    // condizioni particolari, come l'invulnerabilità, che possono impedire
    // l'applicazione del danno.
    //
    // La versione di Giocatore restituisce un bool:
    // true  -> la vita è stata effettivamente diminuita;
    // false -> il danno non è stato applicato.
    //
    // In questo modo Level e le funzioni di collisione non devono conoscere
    // direttamente lo stato di invulnerabilità del giocatore: si limitano a
    // chiamare diminuisciVita() e controllarne il risultato.

    bool diminuisciVita( int danno ) ;

};





#endif //GIOCATORE_H