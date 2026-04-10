#include <iostream>
#include "Map.hpp"

struct node{
    int levelID;
    Map* map;
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

