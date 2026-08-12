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

    void goToNext();

    void goToPrev();  

    //Creazione dei 5 livelli
    void Create_Levels();

    node* getCurrent();
};

#endif
