#include "Map.hpp"
#include "Item.h"
#include "Personaggio.hpp"
#include "NemicoInseguitore.h"
#include "NemicoRandom.h"
#pragma once 
//Legge il file una sola volta durante la compilazione

const int MAX_NEMICI_INS = 10;
const int MAX_NEMICI_RND = 10;
const int MAX_ITEMS = 10;

class Level{
private:
    Map& map;

    /*
    Tolto l'array generico per i nemici e aggiunti i due specifici
    Personaggio nemici[MAX_NEMICI];
    int num_nemici;
    */
    NemicoInseguitore nemici_inseguitore[MAX_NEMICI_INS];
    int num_nemici_ins;

    NemicoRandom nemici_random[MAX_NEMICI_RND];
    int num_nemici_rnd;

    Item items[MAX_ITEMS];
    int num_items;

    bool completato;

public:

    Level(Map& m, int chasers_enemies, int random_enemies, int items); 

    Map& getMap();

    void addEnemies(Personaggio& p);

    void updateEnemies(Personaggio& p);

    void addItem(Item& i);

    void updateItems(Item& i);

};