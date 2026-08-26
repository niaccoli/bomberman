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

    bool goToNext( );
    //Andrea: aggiungere controllo se il livello e' completato va eliminato il nodo
    //se esiste un livello sucessivo aggiorna current e ritorna true, false altrimenti

    bool goToPrev( );
    //Andrea: aggiungere controllo se il livello e' completato va eliminato il nodo
    //se esiste un livello precedente aggiorna current e ritorna true, false altrimenti

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

    bool updateLevels( ) ;
    /* per tutti i livelli non correnti → Level::updateLevel() //aggiorna soltanto i timer dei potenziamenti
     livello corrente  → Level::updateLevel(g) // deve ritornare questo valore cosi' sappiamo se il giocatore e' stato colpito
     */

    bool isLastLevel( ) ;
    //ritorna true se il livello corrente e' l'ultimo livello rimasto

};

#endif
