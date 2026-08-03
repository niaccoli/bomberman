#ifndef BIDIRECTIONALLIST_HPP
#define BIDIRECTIONALLIST_HPP
#include <iostream>
#include "Level.hpp"

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
