#include "BidirectionalList.hpp"

BidirectionalList::BidirectionalList(){
    head = NULL;
    current = NULL;
}

BidirectionalList::BidirectionalList(node* HEAD, node* CURRENT){
    head = HEAD;
    current = CURRENT;
}

void BidirectionalList::goToNext(){
    if(current->next != NULL)
        current = current->next;
}

void BidirectionalList::goToPrev(){
    if(current->prev != NULL)
        current = current->prev;
}