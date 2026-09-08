#ifndef BOMBERMAN_BOMBA_H
#define BOMBERMAN_BOMBA_H

#include "Posizione.h"

class Bomba {
protected:

    // Posizione corrente della bomba; {-1, -1} indica che non è posizionata sulla mappa
    Posizione posizione;

    // Valori standard della bomba senza potenziamenti
    const int defaultDanno = 1;
    const int defaultRaggio = 1;

    // Durate espresse in millisecondi
    const int defaultTimer = 2000;
    const int durataDefaultPotenziamentoDanno = 10000;
    const int durataDefaultPotenziamentoRaggio = 10000;
    const int durataDefaultPotenziamentoTimer = 10000;

    // Imposta la durata residua del potenziamento del danno
    void setDurataPotenziamentoDanno(int durata);

    // Imposta la durata residua del potenziamento del raggio
    void setDurataPotenziamentoRaggio(int durata);

    // Imposta la durata residua del potenziamento del timer
    void setDurataPotenziamentoTimer(int durata);


    // Tempo rimanente prima dell'esplosione, espresso in millisecondi
    int timer;

    // Danno inflitto dall'esplosione
    int danno;

    // Numero di celle raggiunte dall'esplosione in ogni direzione
    int raggio;

    // Indica se la bomba è attualmente posizionata e innescata
    bool attivo;

    // Impedisce di diminuire il timer nello stesso ciclo in cui la bomba viene innescata
    bool appenaInnescata;


    // Indica se è attivo il potenziamento del danno
    bool potenziamentoDanno;

    // Tempo rimanente del potenziamento del danno
    int durataPotenziamentoDanno;


    // Indica se è attivo il potenziamento del raggio
    bool potenziamentoRaggio;

    // Tempo rimanente del potenziamento del raggio
    int durataPotenziamentoRaggio;


    // Indica se è attivo il potenziamento che riduce il tempo di esplosione
    bool potenziamentoTimer;

    // Tempo rimanente del potenziamento del timer
    int durataPotenziamentoTimer;


public:

    // Crea una bomba disattivata, posizionata fuori dalla mappa e con valori standard
    Bomba();


    // Restituisce la coordinata x della bomba
    int getX() const;

    // Restituisce la coordinata y della bomba
    int getY() const;

    // Restituisce la posizione della bomba
    Posizione getPosizione() const;

    // Modifica la coordinata x della bomba
    void setX(int x);

    // Modifica la coordinata y della bomba
    void setY(int y);

    // Imposta la posizione della bomba
    void setPosizione(Posizione posizione);

    // Imposta la posizione della bomba tramite coordinate x e y
    void setPosizione(int x, int y);


    // Restituisce il tempo rimanente prima dell'esplosione
    int getTimer() const;

    // Imposta il tempo rimanente prima dell'esplosione
    void setTimer(int tempo);

    // Diminuisce il timer della quantità specificata
    void diminuisciTimer(int durata);


    // Restituisce il danno inflitto dalla bomba
    int getDanno() const;

    // Imposta il danno della bomba
    void setDanno(int danno);

    // Raddoppia il danno della bomba
    void duplicaDanno();


    // Restituisce il raggio dell'esplosione
    int getRaggio() const;

    // Imposta il raggio dell'esplosione
    void setRaggio(int raggio);

    // Raddoppia il raggio dell'esplosione
    void raddoppiaRaggio();


    // Restituisce true se la bomba è attualmente innescata
    bool innescata() const;

    // Innesca la bomba e inizializza il timer al valore standard
    void innesca();

    // Disattiva la bomba dopo l'esplosione
    void esplodi();

    // Aggiorna il timer della bomba e restituisce true quando la bomba esplode
    bool aggiornaBomba(int durata);


    // ---------------- POTENZIAMENTO DANNO ----------------

    // Attiva il potenziamento del danno oppure ne prolunga la durata se già attivo
    void attivaPotenziamentoDanno();

    // Disattiva il potenziamento e ripristina il danno standard
    void disattivaPotenziamentoDanno();

    // Diminuisce la durata residua del potenziamento del danno
    void diminuisciDurataPotenziamentoDanno(int durata);

    // Restituisce la durata residua del potenziamento del danno
    int getDurataPotenziamentoDanno() const;

    // Restituisce true se il potenziamento del danno è attivo
    bool potenziamentoDannoAttivo() const;

    // Aggiorna la durata del potenziamento e lo disattiva quando scade
    void aggiornaPotenziamentoDanno(int durata);


    // ---------------- POTENZIAMENTO RAGGIO ----------------

    // Attiva il potenziamento del raggio oppure ne prolunga la durata se già attivo
    void attivaPotenziamentoRaggio();

    // Disattiva il potenziamento e ripristina il raggio standard
    void disattivaPotenziamentoRaggio();

    // Diminuisce la durata residua del potenziamento del raggio
    void diminuisciDurataPotenziamentoRaggio(int durata);

    // Restituisce la durata residua del potenziamento del raggio
    int getDurataPotenziamentoRaggio() const;

    // Restituisce true se il potenziamento del raggio è attivo
    bool potenziamentoRaggioAttivo() const;

    // Aggiorna la durata del potenziamento e lo disattiva quando scade
    void aggiornaPotenziamentoRaggio(int durata);


    // ---------------- POTENZIAMENTO TIMER ----------------

    // Attiva il potenziamento che velocizza l'esplosione oppure ne prolunga la durata
    void attivaPotenziamentoTimer();

    // Disattiva il potenziamento del timer
    void disattivaPotenziamentoTimer();

    // Diminuisce la durata residua del potenziamento del timer
    void diminuisciDurataPotenziamentoTimer(int durata);

    // Restituisce la durata residua del potenziamento del timer
    int getDurataPotenziamentoTimer() const;

    // Restituisce true se il potenziamento del timer è attivo
    bool potenziamentoTimerAttivo() const;

    // Aggiorna la durata del potenziamento e lo disattiva quando scade
    void aggiornaPotenziamentoTimer(int durata);


    // Aggiorna contemporaneamente la durata di tutti i potenziamenti della bomba
    void aggiornaPotenziamenti(int durata);

    // Disattiva tutti i potenziamenti e ripristina i valori standard della bomba
    void disattivaPotenziamenti();
};

#endif // BOMBERMAN_BOMBA_H