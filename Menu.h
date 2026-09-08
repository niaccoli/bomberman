//
// Created by andre on 07/09/2026.
//

#ifndef BOMBERMAN_MENU_H
#define BOMBERMAN_MENU_H
#include <curses.h>

class Menu {
protected:
    WINDOW* win ;

    // Indice dell'opzione attualmente selezionata.
    // 0 = Nuova partita
    // 1 = Classifica
    // 2 = Info
    // 3 = Uscita
    int selezione ;

    const int altezza = 11 ;

    const int larghezza = 43 ;

public:
    // Crea la finestra del menu e inizializza
    // la selezione sulla prima opzione.
    Menu() ;

    // Visualizza tutte le opzioni del menu.
    // L'opzione attualmente selezionata viene evidenziata in grassetto.
    void stampa() ;

    // Legge un carattere dalla finestra del menu.
    // Se il carattere non è INVIO, aggiorna la selezione
    // chiamando gestisciInput().
    // Restituisce il carattere letto.
    int leggiInput() ;

    // Gestisce i comandi di navigazione del menu.
    // W sposta la selezione verso l'alto,
    // S sposta la selezione verso il basso.
    // La selezione è circolare: superando la prima o l'ultima
    // opzione si passa rispettivamente all'ultima o alla prima.
    // Dopo l'aggiornamento ristampa il menu.
    void gestisciInput(char input) ;

    // Restituisce l'indice dell'opzione attualmente selezionata.
    int getSelezione() const;

    // Visualizza la schermata contenente le informazioni di gioco:
    // comandi, tipologie di nemici, item e sistema di punteggio.
    // Attende la pressione di INVIO prima di tornare al menu.
    void mostraInfo( ) const;
};


#endif //BOMBERMAN_MENU_H