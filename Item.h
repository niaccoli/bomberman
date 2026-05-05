#ifndef BOMBERMAN_ITEMS_H
#define BOMBERMAN_ITEMS_H

class Item{
    protected:
        int x;
        int y;
        char tipo; //invulnerabilità('I'), riduzione tempo bomba('T'), aumento raggio bomba('B'), 1pt.vita('V'), aumento velocità? pistola?
        int durata; //per quanto rempo rimane sulla mappa
        bool attivo;//il tempo per quanto dura il suo effetto lo mettiamo in una funzione generale


    public:
        Item();
        Item(int x, int y, char tipo, int durata, bool attivo);

        void setX(int x);
        void setY(int y);
        int getX() const;
        int getY() const;

        void setTipo(char tipo);
        char getTipo() const;

        void setDurata(int tempo);
        int getDurata() const;

        bool isAttivo() const;
        void raccogli();
        void disattiva();
        void aggiornaItem();

};



#endif //BOMBERMAN_ITEMS_H