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
    Map* map1 = new Map(21, 41);
    Map* map2 = new Map(24, 46);
    Map* map3 = new Map(30, 30);
    Map* map4 = new Map(30, 30);
    Map* map5 = new Map(30, 30);

    //Inizializzazione mappe
    map1->Initialize_Map(1);
    map2->Initialize_Map(2);
    map3->Initialize_Map(3);
    map4->Initialize_Map(4);
    map5->Initialize_Map(5);

    
    //Creazione nodi lista
    node* node1 = new node;

    node1->levelID = 1;
    node1->level = new Level(*map1, 0, 3,  1);
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

bool BidirectionalList::goToNext( ){
    if(current->next != NULL){

        node* next_node = current->next;

        if(current->level->isCompletato()){
            deleteNode();
        }

        current = next_node;
        return true;
    }
     
    return false;
}

bool BidirectionalList::goToPrev(){
    if(current->prev != NULL){

        node* previous_node = current->prev;

        if(current->level->isCompletato()){
            deleteNode();
        }
            
        current = previous_node;
        return true;
    }
        
    return false;
}

node* BidirectionalList::getCurrent(){
    return this->current;
}


void BidirectionalList::applicaEffettoItem(Giocatore& g, char type){
    if( type == 'I')
        g.invulnerabilitaOn(5);

    else if(type == 'V')
        g.aumentaVita();

    else{
        node* tmp = head;

        while(tmp != NULL){
            tmp->level->applicaEffetto(type);
            tmp = tmp->next;
        }
    }
}

void BidirectionalList::deleteNode(){
    //Variabile di appoggio per poter restituire il puntatore corretto
    node* to_delete = this->current;

    //Controllo che il nodo da eliminare non sia la testa
    if(to_delete->prev != NULL)
        to_delete->prev->next = to_delete->next;
    else
       this->head = to_delete->next;

    //Controllo che il nodo da eliminare non sia la coda
    if(to_delete->next != NULL)
        to_delete->next->prev = to_delete->prev;

    //Eliminazione effettiva del nodo
    delete to_delete->level;
    delete to_delete;
}

bool BidirectionalList::updateLevels(Giocatore& g){
    node* tmp = head;

    bool is_hitted = false;

    while(tmp != NULL){
        if(tmp != current)
            tmp->level->updateLevel();
        else
            is_hitted = current->level->updateLevel(g);
        tmp = tmp->next;
    }

    return is_hitted;
}

bool BidirectionalList::isLastLevel(){
    if(current->next == NULL && current->prev == NULL)
        return true;
    return false;
}

void BidirectionalList::reset_v1(){
    node* tmp = head;

        while(tmp != NULL){
            tmp->level->reset_v1();
            tmp = tmp->next;
        }
}



