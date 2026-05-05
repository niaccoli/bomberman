#ifndef BOMBERMAN_BOMBE_H
#define BOMBERMAN_BOMBE_H


class Bomba {
    protected:
        int x;
        int y;
        int timer; //tempo che la bomba impiega ad esplodere
        int danno;
        int raggio;
        bool attivo;

        bool boostDanno;
        int durataBoostDanno;

        bool boostRaggio;
        int durataBoostRaggio;

        bool boostTimer;
        int durataBoostTimer;

/*da ragionare: una volta che viene viene raccoloto un item bisogna applicare un effetto(funzione void effetto item()).
 *Se l'item è un item che riguarda il giocatore è facile perchè il giocatore è già creato.
 *Es. invulnerabilità fai invulnerabilitaOn() e diminuisci il  *tempoinvulnerabilità ogni ciclo (aggiornaInvulnerabilità()).
 *le bombe invece vengono create ogni volta che il giocatore preme  *'x' quindi forse non ha senso salvare boostpotenza,
 *boostraggio, boostTimer perchè ogni volta si crea una nuova bomba.
 *Forse conviene creare delle sottoclassi di bomba (bombaPotenziata, aumentata, velocizzata)
 *ma anche in questo caso per quanto tempo devono continuare ad essere create questo tipo di bombe dove lo salvo?
 *potrei fare una classe o struttura effettoBomba{char tipo; int tempo; bool attivo;}, quando viene raccolto un item,
 *viene creato un effettoBomba con bool attivo, quindi aggiungere in gestisciInput(piazzaBomba) un controllo su ..
 *
 *forse sto ragionando male:
 *non conviene creare una bomba ogni volta che il giocatore preme 'x' conviene creare un unico oggetto bomba e passarlo per
 *riferimento.
 *In questo caso però il giocatore non deve essere in grado di piazzare una nuova bomba finche la prima non è esplosa.*
 *quindi: nel main creo un unico oggetto Bomba bombastd() posizionata fuori dalla mappa e disattiva.
 *poi nel comando piazza bomba permetto di piazzare la bomba solo se non è già attiva, poisiziono la bomba nelle coordinate del giocatore
 *e la attivo.*
 *a questo punto mi conviene creare dei booleani per i potenziamenti e il tempo del potenziamento, se il giocatore passa sopra un item
 *disattivo l'item e applico il suo effetto attivando il potenziamento che dopo un po si disattiva. (applicaEffettoItem)*/





        //bool checkTimer(); valutare se aggiungerle per verificare che l'oggetto venga chiamato con un timer positivo
        //bool checkRaggio(); valutare se aggiungerle per verificare che l'oggetto venga chiamato con un timer positivo

    public:
        Bomba();

        /*Bomba(int x, int y, int timer, int danno, int raggio, bool attivo); //capire se aggiungere funzioni di check per valori
        // timer, danno, raggio (>0)*/

        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);

        int getTimer() const;
        void setTimer(int tempo);
        void diminuisciTimer();
        void dimezzaTimer(); //forse meglio velocizza (per item 'T' = diminuzione tempo esplosione)

        int getDanno() const;
        void setDanno(int danno);
        void duplicaDanno(); //o potenziaDanno() (per item 'D' = aumento danno bomba (creare nemici tank con 2 vite))

        int getRaggio() const;
        void setRaggio(int raggio);
        void raddoppiaRaggio();  //o aumentaRaggio() (per item 'B' = aumento raggio bomba)

        bool attivata() const; //o innescata
        void setAttivo(bool attivo);
        void attiva();
        void disattiva(); //fose semanticamente più bello esplodi
        void aggiornaBomba();

        //POTENZIAMENTI
        void attivaBoostDanno();
        void disattivaBoostDanno();
        void setDurataBoostDanno(int durata);
        void diminuisciDurataBoostDanno();
        int getDurataBoostDanno() const;
        bool boostDannoAttivo() const;
        void aggiornaBoostDanno();

        void attivaBoostRaggio();
        void disattivaBoostRaggio();
        void setDurataBoostRaggio(int durata);
        void diminuisciDurataBoostRaggio();
        int getDurataBoosRaggio() const;
        bool boostRaggioAttivo();
        void aggiornaBoostRaggio();

        void attivaBoostTimer();
        void disattivaBoostTimer();
        void setDurataBoostTimer(int durata);
        void diminuisciDurataBoostTimer();
        int getDurataBoostTimer() const;
        bool boostTimerAttivo();
        void aggiornaBoostTimer();




};

#endif //BOMBERMAN_BOMBE_H