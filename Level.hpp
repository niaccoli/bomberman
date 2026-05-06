#include "Map.hpp"
#include "Item.h"
#include "Personaggio.hpp"

const int MAX_NEMICI = 10;
const int MAX_ITEMS = 10;

class Level{
private:
    Map& map;

    
    Personaggio nemici[MAX_NEMICI];
    int num_nemici;

    Item items[MAX_ITEMS];
    int num_items;

    bool completato;

public:

    Level(Map& m, int enemies, int items); 

    Map& getMap();

    void addEnemies(Personaggio& p);

    void updateEnemies(Personaggio& p);

    void addItem(Item& i);

    void updateItems(Item& i);

};