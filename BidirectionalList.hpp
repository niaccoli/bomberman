#ifndef BIDIRECTIONALLIST_HPP
#define BIDIRECTIONALLIST_HPP
#include <iostream>
#include "Level.hpp"

/*Io terrei BidirectionalList come vera classe separata. Non la sposterei dentro funzioni.cpp.

Il motivo è che la lista bidirezionale non è una semplice utility: ha uno stato proprio (head, current) e operazioni che
modificano quello stato, come goToNext(), goToPrev() e getCurrent().
Questo è esattamente il tipo di cosa che ha senso rappresentare con una classe.*/

struct node{
    int levelID;
    Level* level;
    node* next;
    node* prev;
};

class BidirectionalList {
protected:
    node* head;
    node* current;
public:
    BidirectionalList();
    BidirectionalList(node* head, node* current);

    void goToNext(Giocatore& g);
    //Andrea: aggiungere controllo se il livello e' completato va eliminato il nodo
    /*  1. verificare se esiste il livello destinazione
        2. ricordare il livello che sto lasciando
        3. cambiare current
        4. posizionare il giocatore sulla porta corretta
        5. se il vecchio livello era completato, eliminarlo */

    void goToPrev(Giocatore& g);
    //Andrea: aggiungere controllo se il livello e' completato va eliminato il nodo

    //Creazione dei 5 livelli
    void Create_Levels();

    node* getCurrent();


    //resetLevels_v1
    //resetLevels_v2
    //deve chiamare ripetutamente Level::reset( ) per rispristinare i livelli quando il giocatore perde una vita
    //non necessaria nell'immediato, prima facciamo una versione semplice dove rimettiamo semplicemente il giocatore
    //al livello 1


    //Andrea x Matte:
    void applicaEffettoItem ( Giocatore& g, char tipo ) ;
    // se tipo == 'I' g.invulnerabilitaOn()
    //se tipo == 'V' g.aumentaVita()
    //altrimenti chiami per tutti i livelli Level::applicaEffetto( tipo )

    void updateLevels( ) ;
    /* per tutti i livelli non correnti → Level::updateLevel() //aggiorna soltanto i timer dei potenziamenti
     livello corrente  → Level::updateLevel(g) // deve ritornare questo valore cosi' sappiamo se il giocatore e' stato colpito
     */

};

#endif
