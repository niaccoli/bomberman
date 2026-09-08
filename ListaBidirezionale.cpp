#include "ListaBidirezionale.hpp"
#include "Livello.hpp"

ListaBidirezionale::ListaBidirezionale(){
    head = NULL;
    current = NULL;
}

ListaBidirezionale::ListaBidirezionale(node* HEAD, node* CURRENT){

    head = HEAD;
    current = CURRENT;
}

ListaBidirezionale::~ListaBidirezionale() {
    node* current_node = head;
    
    while (current_node != nullptr) {
        node* prossimo_nodo = current_node->next;
        
        delete current_node->level;
        delete current_node;
        
        current_node = prossimo_nodo;
    }
}

void ListaBidirezionale::CreaLivelli(){

    //Creazione delle mappe
    //parametri momentanei
    Mappa* mappa1 = new Mappa(21, 40);
    Mappa* mappa2 = new Mappa(21, 42);
    Mappa* mappa3 = new Mappa(21, 41);
    Mappa* mappa4 = new Mappa(23, 46);
    Mappa* mappa5 = new Mappa(27, 47);

    //Inizializzazione mappe
    mappa1->inizializzaMappa(1);
    mappa2->inizializzaMappa(2);
    mappa3->inizializzaMappa(3);
    mappa4->inizializzaMappa(4);
    mappa5->inizializzaMappa(5);

    
    //Creazione nodi lista
    node* node1 = new node;

    node1->levelID = 1;
    node1->level = new Livello(*mappa1, 7, 7, 3);
    node1->prev = NULL;

    node* node2 = new node;

    node1->next = node2;

    node2->levelID = 2;
    node2->level = new Livello(*mappa2, 2, 4, 5);
    node2->prev = node1;

    node* node3 = new node;

    node2->next = node3;

    node3->levelID = 3;
    node3->level = new Livello(*mappa3, 3, 3, 1, 7);
    node3->prev = node2;

    node* node4 = new node;

    node3->next = node4;

    node4->levelID = 4;
    node4->level = new Livello(*mappa4, 3, 1, 2, 4);
    node4->prev = node3;

    node* node5 = new node;

    node4->next = node5;

    node5->levelID = 5;
    node5->level = new Livello(*mappa5, 3, 1, 4, 5);
    node5->prev = node4;

    node5->next = NULL;


    //Assegnazione all'oggetto di tipo BidirectionalList
    this->head = node1;
    this->current = node1;
 
}

bool ListaBidirezionale::goToNext( ){
    if(current->next != NULL){

        node* prossimo_nodo = current->next;

        if(current->level->isCompletato()){
            eliminaNodo();
        }

        current = prossimo_nodo;
        return true;
    }
     
    return false;
}

bool ListaBidirezionale::goToPrev(){
    if(current->prev != NULL){

        node* nodo_precedente = current->prev;

        if(current->level->isCompletato()){
            eliminaNodo();
        }
            
        current = nodo_precedente;
        return true;
    }
        
    return false;
}

node* ListaBidirezionale::getCurrent(){
    return this->current;
}


void ListaBidirezionale::applicaEffettoItem(Giocatore& g, char type){
    if( type == 'I')
        g.invulnerabilitaOn();

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

void ListaBidirezionale::eliminaNodo(){
    //Variabile di appoggio per poter restituire il puntatore corretto
    node* nodo_da_eliminare = this->current;

    //Controllo che il nodo da eliminare non sia la testa
    if(nodo_da_eliminare->prev != NULL)
        nodo_da_eliminare->prev->next = nodo_da_eliminare->next;
    else
       this->head = nodo_da_eliminare->next;

    //Controllo che il nodo da eliminare non sia la coda
    if(nodo_da_eliminare->next != NULL)
        nodo_da_eliminare->next->prev = nodo_da_eliminare->prev;

    //Eliminazione effettiva del nodo
    delete nodo_da_eliminare->level;
    delete nodo_da_eliminare;
}

void ListaBidirezionale::muoviNemici(Giocatore& g) {
    return (current -> level -> muoviNemici( g )) ;
}

bool ListaBidirezionale::collisioniGiocatoreNemici(Giocatore& g) {
    return (current -> level -> collisioneGiocatoreNemici_v2(g)) ;
}

void ListaBidirezionale::updateBoostBombe(int durata) {
    node* temp = head ;

    while ( temp != nullptr ) {
        temp -> level -> aggiornaPotenziamenti(durata) ;
        temp = temp -> next ;
    }
}


bool ListaBidirezionale::aggiornaBomba(Giocatore& g, int durata) {
    return current -> level -> aggiornaEsplosioni(g, durata ) ;
}

bool ListaBidirezionale::isUltimoLivello(){
    if(current->next == NULL && current->prev == NULL)
        return true;
    return false;
}

void ListaBidirezionale::reset_v1(){
    node* tmp = head;

        while(tmp != NULL){
            tmp->level->resetBombeEPotenziamenti();
            tmp = tmp->next;
        }
}

void ListaBidirezionale::reset_v3( ) {
    node* temp = head ;

    while ( temp != nullptr) {
        if ( temp == current) {
            temp -> level -> reset_v3() ;
        }
        else
            temp -> level -> resetBombeEPotenziamenti() ;

        temp = temp -> next ;
    }
}



