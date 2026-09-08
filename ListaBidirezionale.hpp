#ifndef LISTABIDIREZIONALE_HPP
#define LISTABIDIREZIONALE_HPP
#include <iostream>
#include "Livello.hpp"

// Struttura del nodo per la lista doppiamente concatenata
struct node {
    int levelID;
    Livello* level;
    node* next;
    node* prev;
};

class ListaBidirezionale {
protected:
    node* head;
    node* current;

public:
    // Costruttore di default: inizializza una lista vuota.
    ListaBidirezionale();

    //Distruttore per la fine del gioco per evitare memory leak
    ~ListaBidirezionale();
    
    // Costruttore con parametri: inizializza la lista con una testa e un nodo corrente specificati.
    ListaBidirezionale(node* head, node* current);

    // Istanzia, inizializza e concatena i 5 livelli di gioco, impostando le rispettive mappe.
    void CreaLivelli();

    // Avanza al livello successivo. Se il livello appena lasciato è contrassegnato come completato, 
    // lo elimina definitivamente dalla lista. Ritorna true in caso di successo, false altrimenti.
    bool goToNext();

    // Retrocede al livello precedente. Se il livello appena lasciato è contrassegnato come completato, 
    // lo elimina definitivamente dalla lista. Ritorna true in caso di successo, false altrimenti.
    bool goToPrev();

    // Restituisce un puntatore al nodo (livello) in cui si trova attualmente il giocatore.
    node* getCurrent();

    // Verifica se il livello corrente è l'unico rimasto attivo nella lista.
    bool isUltimoLivello();

    // Rimuove il nodo corrente dalla lista e aggiorna i puntatori dei nodi adiacenti.
    void eliminaNodo();


    // Applica l'effetto del potenziamento raccolto. Modifica direttamente il giocatore (es. vita, invulnerabilità) 
    // oppure propaga l'effetto globale (es. potenziamenti bomba) a tutti i livelli attivi.
    void applicaEffettoItem(Giocatore& g, char tipo);

    // Gestisce il movimento di tutti i nemici presenti nel livello corrente.
    void muoviNemici(Giocatore& g);

    // Verifica eventuali collisioni fatali tra il giocatore e i nemici nel livello corrente.
    bool collisioniGiocatoreNemici(Giocatore& g);

    // Aggiorna lo stato della bomba innescata (timer ed esplosione) all'interno del livello corrente.
    bool aggiornaBomba(Giocatore& g, int durata);

    // Aggiorna la durata residua dei potenziamenti (es. raggio o timer bomba) su tutti i livelli attivi.
    void updateBoostBombe(int durata);

    // Disattiva i potenziamenti della bomba su tutti i livelli.
    void reset_v1();

    // Esegue un reset totale (entità e potenziamenti) per il livello corrente in caso di morte del giocatore, 
    // e si limita a resettare bombe e potenziamenti per i livelli in background.
    void reset_v3();
};

#endif