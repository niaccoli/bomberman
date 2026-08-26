#include "BidirectionalList.hpp"
#include "Level.hpp"

BidirectionalList::BidirectionalList(){
    head = NULL;
    current = NULL;
}

BidirectionalList::BidirectionalList(node* HEAD, node* CURRENT){
    head = HEAD;
    current = CURRENT;
}

void BidirectionalList::Create_Levels(){

    //Creazione delle mappe
    //parametri momentanei
    Map* map1 = new Map(21, 41, 3, 5);
    Map* map2 = new Map(24, 46, 19, 10);
    Map* map3 = new Map(1, 1, 1, 1);
    Map* map4 = new Map(1, 1, 1, 1);
    Map* map5 = new Map(1, 1, 1, 1);

    //Inizializzazione mappe
    map1->Initialize_Map(1);
    map2->Initialize_Map(2);
    map3->Initialize_Map(3);
    map4->Initialize_Map(4);
    map5->Initialize_Map(5);

    
    //Creazione nodi lista
    node* node1 = new node;

    node1->levelID = 1;
    node1->level = new Level(*map1, 1, 1, 1);
    node1->prev = NULL;

    node* node2 = new node;

    node1->next = node2;

    node2->levelID = 2;
    node2->level = new Level(*map2, 2, 2, 2);
    node2->prev = node1;

    node* node3 = new node;

    node2->next = node3;

    node3->levelID = 3;
    node3->level = new Level(*map3, 3, 3, 3);
    node3->prev = node2;

    node* node4 = new node;

    node3->next = node4;

    node4->levelID = 4;
    node4->level = new Level(*map4, 4, 4, 4);
    node4->prev = node3;

    node* node5 = new node;

    node4->next = node5;

    node5->levelID = 5;
    node5->level = new Level(*map5, 5, 5, 5);
    node5->prev = node4;

    node5->next = NULL;


    //Assegnazione all'oggetto di tipo BidirectionalList
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
    return this->current;
}

void BidirectionalList::applicaEffettoItem(Giocatore& g, char type){
    if(type == 'I')
        g.invulnerabilitaOn(5);

    else if(type == 'V')
        g.aumentaVita();

    else
        current->level->applicaEffetto(type);
}



