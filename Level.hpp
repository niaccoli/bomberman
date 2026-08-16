#include "Map.hpp"
#include "Item.h"
#include "Personaggio.hpp"
#include "Giocatore.h"
#include "Bomba.h"
#include "NemicoInseguitore.h"
#include "NemicoRandom.h"
#pragma once

const int MAX_NEMICI_INS = 10;
const int MAX_NEMICI_RND = 10;
const int MAX_ITEMS = 10;

class Level {
private:
    Map& map;

    NemicoInseguitore nemici_inseguitore[MAX_NEMICI_INS];
    int num_nemici_ins;

    NemicoRandom nemici_random[MAX_NEMICI_RND];
    int num_nemici_rnd;
    //idea: ogni livello avra' un certo numero di nemici_inseguitore e un certo numero di nemici_random.
    //Noi consideriamo come validi solo i primi num_nemici.


    Bomba b ;

    Item items[MAX_ITEMS];
    int num_items;
    //int next_item ; //da introdurre se si vuole usare Level::reset()

    bool completato;

    Posizione posizioneRandomValida() ;
    //ritorna una posizione casuale: dentro la mappa, non muro, non occupata;

    void posizionaNemici( ) ;
    //posiziona i nemici validi in diverse posizioni valide causali valide ( dentro la mappa, non muro, non occupate )

    int isThereARandomEnemy ( Posizione posizione ) ;
    //se presente un nemico_random vivo in posizione ritorna l'indice del nemico, altrimenti ritorna -1

    int isThereAInsEnemy ( Posizione posizione ) ;
    //se presente un nemico_inseguitore vivo in posizione ritorna l'indice del nemico, altrimenti ritorna -1


    /*

    /* valutare se avere un solo oggetto Bomba per il giocatore, riutilizzato ogni volta.
    *   Giocatore g;
        Bomba b;
        BidirectionalList livelli;
    La bomba esiste una sola volta e cambia stato:
    Quando esplode, la disattivi e la stessa b può essere riutilizzata per la bomba successiva.


    problema: "non c'e la possibilita che se la bomba viene piazzata in un livello poi il giocatore va in un altro
    livello prima che la bomba esploda poi la bomba risulti posizionata nel nuovo livello?"

    Sì, è esattamente un problema possibile con l'impostazione “una sola Bomba globale”.
    Esempio:

    Sei nel livello 1.
    Piazzi la bomba in (5, 7).
    La bomba rimane attiva per 4 secondi.
    Prima che esploda passi al livello 2.

    La soluzione più coerente : Se vuoi mantenere una sola bomba, la bomba deve ricordarsi in quale livello è stata piazzata.
     *
     *
    !!! una bomba per livello è probabilmente la soluzione più naturale per la struttura che state costruendo.
    Level 1
        ├── Map
        ├── Nemici
        ├── Item
        └── Bomba

    Level 2
        ├── Map
        ├── Nemici
        ├── Item
        └── Bomba

    Quando sei nel livello 1: current->level->piazzaBomba(g);

    domanda: "se la bomba e stata piazzata e il giocatore si muove di livello e' giusto che la bomba esploda e faccia danno lo stesso?"

    la bomba del livello 1 viene attivata. Se poi passi al livello 2, la bomba resta comunque dentro Level 1.
    C'è però un dettaglio progettuale importante. Se vuoi che:

    la bomba continui il countdown anche mentre il giocatore è in un altro livello
    non puoi aggiornare il timer solo sul livello corrente.

    Per esempio, se il main facesse solo:
    current->level->update();
    la bomba nel livello precedente smetterebbe di essere aggiornata quando cambi livello.

    due possibilità:

    1. I livelli inattivi continuano a vivere
    Aggiornate anche le bombe attive degli altri livelli.
    La bomba esplode dopo 4 secondi indipendentemente da dove si trovi il giocatore.

    2. I livelli vengono "congelati" quando li lasci
    Quando torni nel livello, tutto riprende da dove era rimasto: nemici, bomba, timer ecc.

    non farei più appartenere la bomba al giocatore. La bomba viene piazzata dal giocatore,
    ma una volta piazzata appartiene allo stato del livello, proprio come un item o un nemico. */

public:

    Level(Map& m, int chasers_enemies, int random_enemies, int items);

    Map& getMap( );

    //void addEnemies(Personaggio& p);
    /*Andrea: penso che questa funzione non sia necessaria
     *la mia idea e':
     *nel costruttore di Level noi posizioniamo gia i nemici causalmente nella mappa in posizioni valide
     *cosi abbiamo gia' i livelli creati. Gli item li teniamo non attivi fuori dalla mappa e li droppiamo nella mappa
     *quando un muro viene distrutto o un nemico ucciso.
     *il giocatore lo posizioniamo nel primo livello in una posizione libera casuale
     mentre nei livelli successivi lo posizioniamo a partire dall'entrata nel livello.
     */

    /*risposta chat:
     *il commento ha senso e la scelta progettuale è coerente.
     *se quando costruisci un Level sai già quanti NemicoInseguitore e quanti NemicoRandom deve avere,
     *allora puoi far sì che il costruttore chiami una funzione privata tipo: posizionaNemici(...)
     *e il livello nasce già completo. In quel caso addEnemies() diventa effettivamente ridondante.
     *Anche la distinzione che fai sugli item è corretta: i nemici fanno parte dello stato iniziale del livello,
     *mentre gli item possono partire fuori mappa/inattivi e comparire solo quando avviene un evento di gioco,
     *per esempio la morte di un nemico o la distruzione di un muro.
     *Sul giocatore, invece, concordo con quello che hai scritto nel commento: è diverso.
     *Il giocatore è uno solo e non appartiene permanentemente a un Level,
     *quindi ha senso che venga posizionato dal codice che gestisce l'ingresso nel livello.
*/


    void updateEnemies(Personaggio& p);

    void addItem(Item& i);
    //Andrea: la eliminerei. Gli item vengono creati dal costruttore del livello, posizionati fuori dalla mappa e non
    //attivi. Quando un nemico viene ucciso o un muro viene rotto, gli item vengono droppati nella posizione dell'uccisione
    // o rottura

    void updateItems(Item& i);
    //questa funzione avra' senso quando gli item avranno una durata

    //nel vostro progetto ha senso che la gestione delle collisioni appartenga a Level, perché è Level che conosce gli
    //oggetti presenti nel livello: mappa, nemici e item.
    //più pulito rispetto a passare continuamente Level& alle funzioni.
    //Level possiede/conosce nemici, item e mappa;
    //quindi una funzione che deve controllare tutti i nemici del livello dovrebbe poter usare direttamente i membri del livello;
    //non serve esporre getNemico(i), getNumNemici(), ecc. solo per permettere a una funzione esterna di fare il controllo;


    bool collisioneGiocatoreNemici(Giocatore& g ) ;
    //se il giocatore occpua la stessa posizione di un nemico ritorna true e diminuisce la vita del giocatore di 1.pt
    /*(Andrea) idea per il main:
        *if (collisioneGiocatoreNemici(g)) {
        // il giocatore è stato colpito
        // collisioneGiocatoreNemici ha già diminuito la vita

            if (g.vivo()) {
                // torna al primo livello
            }
            else {
                // game over
            }
        }
        */
    //DA DECIDERE: "ricomincia dal primo livello": tornare semplicemente al Level 1 mantenendo lo stato dei livelli,
    //oppure resettare completamente nemici/item/bombe come a inizio partita.

    void collisioneEsplosione(Giocatore& g ) ;
    //anziche' avere un unica funzione che controlla le collisioni dell'esplosione con giocatori, muri, nemici
    /*creo 3 funzioni
    *bool collisioneEsplosioneGiocatore(Giocatore& g);
    void collisioneEsplosioneMuri();
    void collisioneEsplosioneNemici();

    mia idea:
    1. collisione col giocatore
    2. se vivo → torna subito al livello 1
    3. collisione muri
    4. collisione nemici

CHAT: Io non cambierei livello al punto 2.
Ricorda che la bomba appartiene al Level corrente. Se sei nel livello 3 e la bomba esplode, quell'esplosione deve finire
di produrre tutti i suoi effetti nel livello 3, anche se ha colpito il giocatore.
suggerisce:
bool giocatoreColpito = collisioneEsplosioneGiocatore(g);
collisioneEsplosioneMuri();
collisioneEsplosioneNemici();
e solo dopo:
    if (giocatoreColpito) {
    if (g.vivo()) {
        // ritorna al primo livello
    }
    else {
        // game over
    }
}

    bool Level::collisioneEsplosione(Giocatore& g) {

    bool colpito = collisioneEsplosioneGiocatore(g);

    collisioneEsplosioneMuri();
    collisioneEsplosioneNemici();

    return colpito;
}
    Poi il main:
    if (currentLevel.collisioneEsplosione(player)) {

    if (player.vivo())
        // torna al livello 1
    else
        // game over
}

DOMANDA A CHAT:
la mia idea era quella di ripristinare i livelli allo stato originale se il giocatore perde una vita,
per quello non volevo creare un'unica funzione di collisioneEsplosione.
ha senso ripristinare i livelli allo stato iniziale se il giocatore perde una vita?
ho guardato il gioco online, se il giocatore perde una vita cambia completamente la mappa, ma il numero di nemici e muri ricomincia da capo


CHAT:
ha senso resettare il livello quando il giocatore perde una vita.
Però farei una distinzione importante: non parlerei di “ripristinare allo stato originale”, ma di rigenerare il livello nello stato iniziale.
    perdi una vita
        ↓
    il vecchio stato del livello viene scartato
        ↓
    nuova mappa
    nuovi muri
    nemici riposizionati
    item rimossi
    bomba resettata
        ↓
    riparti

    In questo caso la tua idea di separare le collisioni è sensata
    gestire l'esplosione in quest'ordine:
    if (collisioneEsplosioneGiocatore(g)) {

        if (g.vivo()) {
            // reset / rigenera livello
            // riposiziona giocatore
        }
        else {
            // game over
        }

        // non serve controllare muri e nemici
    }
    else {
        collisioneEsplosioneMuri();
        collisioneEsplosioneNemici();
    }

    Però: resetterei il livello corrente, non necessariamente tutti i livelli
    due meccaniche diverse.
    A. Perde una vita → rigenera il livello corrente
    B. Perde una vita → torna al livello 1

    A livello di classi introdurrei proprio reset()
    rigenera/reinizializza mappa
    resetta nemici
    posiziona nuovamente nemici
    disattiva/resetta item
    resetta bomba
    completato = false

    se la mappa dopo la morte deve cambiare, allora non devi salvare una copia della mappa iniziale per ripristinarla.
    Devi richiamare la logica che genera una nuova mappa casuale.

    Quindi nel vostro design vedrei bene una struttura di questo tipo:
        if (level.collisioneGiocatoreNemici(player)) {

        if (player.vivo())
            level.reset();
        else
            // game over

    }
    else if (level.collisioneEsplosioneGiocatore(player)) {

        if (player.vivo())
            level.reset();
        else
            // game over

    }
    else {

        level.collisioneEsplosioneMuri();
        level.collisioneEsplosioneNemici();

        // altre collisioni...
    }


    DOMANDA CHAT:
    supponiamo che se il giocatore perde una vita non resettiamo solo il livello corrente ma tutti i livelli,
    per adesso mantenendo la stessa mappa ma con i nemici posizionati in punti diversi
    ( questo non dovrebbe essere un problema perche' il costruttore li posiziona casualmente).
    La funzione reset e' piu' logico che appartenga a Level o a bidirectional list?

    RISPOSTA CHAT:
    la soluzione più logica è avere entrambe le funzioni, con responsabilità diverse:
    Level::reset()
    BidirectionalList::resetLevels()
    resetta l'intero insieme dei livelli chiamando reset() su ciascun Level.

    È Level che conosce i propri: nemici, item, bomba, completato, mappa
    quindi solo lui dovrebbe sapere come riportare il proprio stato all'inizio.

    */

    void reset() ;
    /*DA DECIDERE:
     *valutare se quando il giocatore perde una vita fare ricominciare il gioco dal primo livello
     *e resettare i nemici e gli item (come nelle versioni online, ma piu' complicato da implementare )
     * altimenti possiamo fare ripartire il giocatore dal livello corrente o dal primo senza resettare i nemici e item
    pero' in quel caso prima di fare ricominciare il livello l'esplosione deve finire di produrre tutti i suoi effetti
    anche se ha colpito il giocatore.


    ATTENZIONE(chat):
    Il costruttore salva:
    num_nemici_ins = chasers_enemies;
    num_nemici_rnd = random_enemies;
    num_items = items;
    Se durante la partita questi contatori vengono decrementati quando muoiono nemici o vengono droppati item,
    al momento del reset non saprai più quanti ce n'erano inizialmente.

    DOMANDA A CHAT:
    alla morte dei nemici la mia intenzione era semplicemente di mettere lo stato del nemico come morto quindi il contatore non cambierebbe,
    il problema e' invece con drop item dove man mano che un item viene droppato diminuivo num_items,
    pero' per quello mi basta aggiungere una campo in Level indicato come next
    _item che indica l'item da droppare cosi da mantenere il num_items invariato
     */



    bool collisioneEsplosioneGiocatore(Giocatore& g ) ;
    /*l'esplosione ha colpito il giocatore?
                ↓
               true
                ↓
        ha ancora vite?
           ↙          ↘
         sì            no
        restart      game over
        */



    void collisioneEsplosioneMuri( ) ;
    /*non bool perche' una singola esplosione potrebbe colpire più oggetti contemporaneamente.
    *esplosione
       ↓
    muro distruttibile colpito?
       ↓ sì
    distruggi muro
       ↓
    provaDropItem(posizione del muro)
    */

    void collisioneEsplosioniNemici( ) ;
    /*esplosione
       ↓
    nemico colpito?
       ↓
    diminuisci vita
       ↓
    nemico morto?
       ↓ sì
    provaDropItem(posizione del nemico)
    */





    void raccoltaItem(Giocatore& g ) ;


    void controllaCollisioni(Giocatore& g ) ;
    //forse piuttosto che un unica funzione conviene utilizzare separatamente:
    //collisioneGiocatoreNemici
    //collisioneEsplosione
    //raccoltaItem

    void dropItem_v1(Posizione posizione) ; //versione senza int next_item ;
    //guarda nore in item.h
    /*  si occupa di:
        1. controllare num_items > 0
        2. stabilire casualmente se fare il drop
        3. prendere items[num_items - 1]
        4. assegnare tipo casuale
        5. assegnare x e y
        6. attivarlo
        7. decrementare num_items


        //non considerare muri per ora
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
               prendi items[num_items - 1 ]
               spostalo in (x,y)
               attivo = true
                setTipoRandom()
                num_items--
        */

    void piazzaBomba(Giocatore& g) ;
    //posiziona una bomba nella posizione occupata dal giocatore e ne attiva il timer (timer default = 4).

    //void applicaEffettoItem ( Item& i );
    //capire se mettere come funzione generale


};