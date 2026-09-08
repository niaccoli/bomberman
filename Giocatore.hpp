#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Personaggio.hpp"

class Giocatore : public Personaggio {
protected:
    // Durata base dell'invulnerabilità, espressa in millisecondi.
    const int defaultTimerInvulnerabilitaMs = 10000 ;

    // Indica se il giocatore è attualmente invulnerabile.
    bool invulnerabilita;

    // Tempo rimanente dell'invulnerabilità, espresso in millisecondi.
    int tempoInvulnerabilita;

    // Punteggio accumulato dal giocatore durante la partita.
    int punteggio ;

public:
    // Crea un giocatore con 3 vite, posizionato fuori dalla mappa,
    // senza invulnerabilità e con punteggio iniziale pari a zero.
    Giocatore();

    // Crea un giocatore con il numero di vite e la posizione specificati,
    // senza invulnerabilità e con punteggio iniziale pari a zero.
    Giocatore(int vite, int x, int y);

    // Crea un giocatore con il numero di vite e la posizione specificati,
    // senza invulnerabilità e con punteggio iniziale pari a zero.
    Giocatore(int vite, Posizione posizione) ;

    // Attiva l'invulnerabilità per la durata base.
    // Se era già attiva, la durata viene prolungata.
    void invulnerabilitaOn (  );

    // Attiva l'invulnerabilità per la durata specificata.
    // Se era già attiva, la durata viene prolungata.
    void invulnerabilitaOn(int durata);

    // Disattiva l'invulnerabilità e azzera il tempo rimanente.
    void invulnerabilitaOff( );

    // Restituisce true se il giocatore è attualmente invulnerabile.
    bool invulnerabile( ) const;

    // Diminuisce il tempo rimanente dell'invulnerabilità.
    // Quando il tempo raggiunge zero, l'invulnerabilità viene disattivata.
    void aggiornaInvulnerabilita(int durata );

    // Diminuisce di una unità la vita del giocatore se non è invulnerabile.
    // Restituisce true se il danno è stato applicato, false altrimenti.
    bool diminuisciVita();

    // Diminuisce la vita del giocatore del danno specificato
    // se il giocatore non è invulnerabile.
    // Restituisce true se il danno è stato applicato, false altrimenti.
    bool diminuisciVita( int danno ) ;

    // Restituisce il punteggio attuale del giocatore.
    int getPunteggio() const;

    // Aumenta il punteggio del giocatore della quantità specificata.
    void aumentaPunteggio( int punti ) ;

};



#endif //GIOCATORE_H