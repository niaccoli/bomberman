#include "Level.hpp"

Level::Level(Map& m, int enemies, int items) : map(m){
    num_nemici = enemies;
    num_items = items;
    completato = false;
};

Map& Level::getMap(){
    return map;
}

void Level::addEnemies(Personaggio& p){
    
}