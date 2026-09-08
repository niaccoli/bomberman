#ifndef BOMBERMAN_ITEMS_H
#define BOMBERMAN_ITEMS_H
#include "Posizione.h"


class Item{
    protected:

        // Posizione corrente dell'item.
        // {-1, -1} indica che l'item non è presente sulla mappa.
        Posizione posizione ;

        // Tipo dell'item:
        // D = aumento danno bomba
        // R = aumento raggio bomba
        // T = riduzione tempo di esplosione
        // I = invulnerabilità
        // V = vita aggiuntiva
        char tipo;

        // Indica se l'item è attualmente presente sulla mappa
        // e può essere raccolto.
        bool attivo;


    public:
    // Crea un item inattivo, senza tipo e posizionato fuori dalla mappa.
        Item();

    // Crea un item con posizione, tipo e stato specificati.
        Item(int x, int y, char tipo, bool attivo);


    // Imposta la coordinata x dell'item.
        void setX(int x) ;

    // Imposta la coordinata y dell'item.
        void setY(int y) ;

    // Imposta la posizione dell'item.
        void setPosizione(Posizione posizione) ;

    // Imposta la posizione dell'item tramite le coordinate x e y.
        void setPosizione(int x, int y) ;

    // Restituisce la coordinata x dell'item.
        int getX() const ;

    // Restituisce la coordinata y dell'item.
        int getY() const ;

    // Restituisce la posizione dell'item.
        Posizione getPosizione( ) const ;

    // Imposta il tipo dell'item.
    // Se il tipo ricevuto non è valido, assegna il carattere spazio.
        void setTipo(char tipo) ;

    // Restituisce il tipo dell'item.
        char getTipo() const ;

    // Assegna casualmente il tipo dell'item secondo
    // le probabilità definite dalla funzione.
        void setTipoRandom() ;

    // Restituisce true se l'item è attualmente presente sulla mappa.
        bool isAttivo() const ;

    // Segna l'item come raccolto, disattivandolo.
        void raccogli() ;

    // Disattiva l'item.
        void disattiva() ;

    // Attiva l'item rendendolo presente sulla mappa.
        void attiva( ) ;


};



#endif //BOMBERMAN_ITEMS_H