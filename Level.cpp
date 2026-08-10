#include "Level.hpp"

Level::Level(Map& m, int chasers_enemies, int random_enemies, int items) : map(m){
    num_nemici_ins = chasers_enemies;
    num_nemici_rnd = random_enemies;
    num_items = items;
    completato = false;
}

Map& Level::getMap(){
    return map;
}

void Level::addEnemies(Personaggio& p){
    //Da scrivere
}

void updateEnemies(Personaggio& p){
    //Da scrivere
}

void Level::addItem(Item& i){
    //Da scrivere
}

void updateItems(Item& i){
    //Da scrivere
}