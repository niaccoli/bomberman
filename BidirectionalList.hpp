#include <iostream>

struct node{
    int levelID;
    //puntatore alla mappa specifica di un determinato livello
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

    node getCurrent();
};

