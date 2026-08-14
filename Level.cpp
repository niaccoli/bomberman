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

void Level::updateEnemies(Personaggio& p){
    //Da scrivere
}

void Level::addItem(Item& i){
    //Da scrivere
}

void Level::updateItems(Item& i){
    //Da scrivere
}

/*void applicaEffettoItem( Item& i, Bomba& b) { //quando il giocatore e l'item hanno la stessa posizione (bool controllaraccoltaitem())
    if (i.getTipo() == 'D') {
        b.attivaBoostRaggio();
    }
    else if (i.getTipo() == 'B') {
        b.attivaBoostDanno();
    }
    else {
        b.attivaBoostTimer();
    }
} //poi Item.raccogli();*/


/*void collisioneGiocatoreNemici (Giocatore& g, Level* l){
 *  for ( int i = 0; i < l.num_nemici_i: i++ )
 *      if ( ( giocatore.getX() == nemici_i[i].getX )  && ( giocatore.getY == nemici_i[i].getY ) )
 *          g.diminuisciVita() ;
 *
*   for ( int i = 0; i < l.num_nemici_r: i++ )
 *      if ( ( giocatore.getX() == nemici_r[i].getX )  && ( giocatore.getY == nemici_r[i].getY ) )
 *          g.diminuisciVita() ;
 *
 *}

/*void collisioneEsplosione(Giocatore& g, Nemico& n[], Mappa& m, Bomba& b);{
 *prende la posizione della bomba
 *prende il raggio della bomba
 *calcola
 *controlla cella per cella
 *se una cella(x,y) == giocatore.posizione
 *      giocatore.diminuisci vita
 *se una cella(x,y) == nemico.posizione
 *      nemico.diminuisci vita
 *se una cella(x, y) == muro distruttibile
 *      muro.distruggi
}*/

//void raccoltaItem(Giocatore& g, Item& i[], Bomba& b) {
//  for(tutti gli item(
//      se giocatore.posizione == item.posizione && item.attivo
//          item.raccogli;
//  applica_effetto_item(i[i], b)
//}


/*void controllaCollisioni(Giocatore& g, Nemico& n[], Mappa& m, Bomba& b, Item i){
 *  collisioneGiocatoreNemici(g, n);
 *  if (giocatore.vivo()) //valutare se lasciare questo controllo, solo che senza la vita del giocatore potrebbe andare in negativo se dopo si prende anche una bomba
 *      if (b.innescata() && bomba.getTimer <= 0)
 *          collisioneEsplosione(g, n, m, b);
 *  if (giocatore.vivo())
 *      raccoltaItem(g, i, b)
 }*/

