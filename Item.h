#ifndef BOMBERMAN_ITEMS_H
#define BOMBERMAN_ITEMS_H


/*mia idea:
 *per ogni livello, quando viene creata la lista di livelli, creiamo un certo numero di oggetti item con un
 *tipo randomico, posizionati fuori dalla mappa, quindi dato che per adesso gli item non hanno durata li metterei
 *attivi ma fuori dalla mappa.
 *Poi se un nemico muore o un muro viene distrutto,
 *se sono ancora presenti item viene fatta una scelta casuale (rand) per decidere se spostare l'item in quel punto della mappa o no
 *
 *
 *risposta chat:
 *Sì, questa impostazione ha senso. Cambierei però un dettaglio: gli item fuori dalla mappa non li considererei attivi.
 *Userei attivo == true per significare “questo item è attualmente presente sulla mappa e può essere raccolto”.
 *
Quindi ogni Level avrebbe, per esempio:

Item items[MAX_ITEMS];
int num_items;
int next_item;

Poi, durante l'inizializzazione del Level, assegni casualmente il tipo ai vari item.

Per esempio concettualmente:

for (int i = 0; i < num_items; i++) {
    items[i].setTipo(tipo casuale );
}

Non metterei necessariamente il rand() dentro al costruttore di Item: preferisco che sia Level a decidere quali item contiene.

Quando muore un nemico in (x,y) oppure viene distrutto un muro in (x,y), fai il lancio casuale:
nemico muore
     ↓
rand()
     ↓
drop item?
  /      \
NO        SI
          ↓
   ci sono ancora item?
       /       \
      NO       SI
                ↓
       prendi items[next_item]
       spostalo in (x,y)
       attivo = true
       next_item++


mia idea: al posto di usare next_items, io posizionerei items[num_items - 1] cosi' da non dover creare un campo
next_item e quando droppi un item fai un pop.
il parametro attivo ha senso che nel costruttore sia false, poi nel dropitem alla morte del nemico l'item viene attivato,
cosi sono gia pronto per implementare in futuro la durata dell'item.

Pero' non sono sicuro se convenga avere
un costruttore che non assegna alcun tipo all'item e assegnare il tipo durante il drop,
oppure avere un costruttore che assegna un tipo randomico durante la creazione


risposta chat:
idea di usare l'array come una specie di stack di item disponibili è buona, ma va precisato cosa significa fare il “pop”.
e num_items rappresenta quanti item non sono ancora stati droppati, allora puoi fare:

Item& i = items[num_items - 1];
i.setX(x);
i.setY(y);
i.attiva();
num_items--;

mia versione:
items[num_items - 1].attiva();
items[num_items - 1].setTipo(...);
items[num_items - 1].setX(x);
items[num_items - 1].setY(y);
num_items--;

Quindi non cancelli realmente l'oggetto dall'array: semplicemente riduci la parte dell'array che consideri ancora “disponibile”.

Su attivo: sono d'accordo con te
Terrei il costruttore con:

attivo = false;

Gli item vengono creati ma non sono presenti sulla mappa.

Quando avviene il drop:

item.setX(x);
item.setY(y);
item.attiva();

e da quel momento attivo == true.

Quando viene raccolto:

item.raccogli();

torna false.

Questo è anche molto comodo quando aggiungerai la durata, perché potrai dire:

attivo = false
→ item non presente
drop
→ attivo = true
→ parte il timer
timer finito / raccolto
→ attivo = false


Tipo random nel costruttore oppure nel drop?
Tra le due possibilità, io sceglierei assegnare il tipo durante il drop, non nel costruttore.


Level::dropItem(int x, int y)
si occupa di:
1. controllare num_items > 0
2. stabilire casualmente se fare il drop
3. prendere items[num_items - 1]
4. assegnare tipo casuale
5. assegnare x e y
6. attivarlo
7. decrementare num_items
*/


class Item{
    protected:
        int x;
        int y;
        char tipo; //invulnerabilità('I'), riduzione tempo bomba('T'), aumento raggio bomba('B'), 1pt.vita('V'), aumento velocità? pistola?
        //int durata; //per quanto rempo rimane sulla mappa
        bool attivo;//il tempo per quanto dura il suo effetto lo mettiamo in una funzione generale


    public:
        Item();
        Item(int x, int y, char tipo, /*int durata,*/ bool attivo);

        void setX(int x);
        void setY(int y);
        int getX() const;
        int getY() const;

        void setTipo(char tipo);
        char getTipo() const;
        void setTipoRandom() ;

        //void setDurata(int tempo);
        //int getDurata() const;

        bool isAttivo() const;
        void raccogli();
        void disattiva();
        //void aggiornaItem();

};



#endif //BOMBERMAN_ITEMS_H