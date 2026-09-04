#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Personaggio.hpp"

class Giocatore : public Personaggio {
protected:
    bool invulnerabilita;
    int tempoInvulnerabilita;
public:
    Giocatore();
    Giocatore(int vite, int x, int y);
    Giocatore(int vite, Posizione posizione) ;

    void invulnerabilitaOn(int durata); //ritorna il tempo di invulnerabilita'

    void invulnerabilitaOn (  ); //attiva invulnerabilita

    void invulnerabilitaOff( ); //distattiva invulnerabilita' e reimposta il tempo invulnerabilita' a zero

    bool invulnerabile( ) const; //ritorna true se invulnerabilita attiva, false altrimenti

    void aggiornaInvulnerabilita( ); //diminuisce il tempo di invulnerabilita', se il tempo arriva a zero la disattiva

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