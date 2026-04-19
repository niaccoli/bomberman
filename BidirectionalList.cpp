#include "BidirectionalList.hpp"

BidirectionalList::BidirectionalList(){
    head = NULL;
    current = NULL;
}

BidirectionalList::BidirectionalList(node* HEAD, node* CURRENT){
    head = HEAD;
    current = CURRENT;
}

void BidirectionalList::Create_Levels(){
    Map* map1 = new Map(21, 41, 1, 1);
    Map* map2 = new Map(24, 46, 19, 10);

    node* node1 = new node;

    node1->levelID = 1;
    node1->map = map1;
    node1->prev = NULL;

    node* node2 = new node;

    node1->next = node2;

    node2->levelID = 2;
    node2->map = map2;
    node2->prev = node1;

    node2->next = NULL; //TEMPORANEO PER TEST
    //node* node3 = new node;
    /*
    node2->next = node3;

    node3->levelID = 3;
    //node3->map = map3;
    node3->prev = node2;
    node3->
    
    node* node4 = new node;

    node3->next = node4;

    node4->levelID = 4;
    node4->map = map4;
    node4->prev = node3;

    node* node5 = new node;

    node4->next = node5;

    node5->levelID = 5;
    node5->map = map5;
    node5->prev = node4;
    node5->next = NULL;
    */


    //Inizializzazione delle 5 mappe con cicli while
    node* tmp = node1;

    while(tmp != NULL){
        tmp->map->Initialize_Map(tmp->levelID);
        tmp = tmp->next;
    }

    //Assegnazione all0oggetto di tipo BidirectionalList
    this->head = node1;
    this->current = node1;
}

void BidirectionalList::goToNext(){
    if(current->next != NULL)
        current = current->next;
}

void BidirectionalList::goToPrev(){
    if(current->prev != NULL)
        current = current->prev;
}

node* BidirectionalList::getCurrent(){
    this->current;
}

