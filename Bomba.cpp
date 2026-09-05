#include "Bomba.h"

Bomba::Bomba():
posizione{ -1, -1 },
timer(0), boostTimer(false), durataBoostTimer(0),
raggio(defaultRaggio), boostRaggio(false), durataBoostRaggio(0),
attivo(false),
danno(defaultDanno), boostDanno(false), durataBoostDanno(0)
{ }


/*Bomba::Bomba(int x, int y, int timer, int danno, int raggio, bool attivo) {
    setX(x);
    setY(y);
    setTimer(timer);
    setDanno(danno);
    setRaggio(raggio);
    setAttivo(attivo);
}*/

int Bomba::getX() const {
    return this -> posizione.x;
}

int Bomba::getY() const {
    return this -> posizione.y;
}

Posizione Bomba::getPosizione() const {
    return this -> posizione ;
}

void Bomba::setX(int x) {
    this -> posizione.x = x;
}

void Bomba::setY(int y) {
    this -> posizione.y = y;
}

void Bomba::setPosizione(Posizione posizione) {
    this -> posizione = posizione ;
}

void Bomba::setPosizione(int x, int y) {
    this -> posizione.x = x ;
    this -> posizione.y = y ;
}


int Bomba::getTimer() const {
    return this -> timer;
}

void Bomba::setTimer(int tempo) {
    this -> timer = tempo;
}

void Bomba::diminuisciTimer() {
    this -> timer-- ;
}

int Bomba::getDanno() const {
    return this -> danno;
}

void Bomba::setDanno(int danno) {
    this -> danno = danno;
}

void Bomba::duplicaDanno() {
    this -> danno *= 2 ;
}

int Bomba::getRaggio() const {
    return this -> raggio;
}

void Bomba::setRaggio(int raggio) {
    this -> raggio = raggio;
}

void Bomba::raddoppiaRaggio() {
    this -> raggio *= 2;
}

bool Bomba::innescata() const {
    return this -> attivo;
}

void Bomba::innesca() {
    this -> attivo = true;
    setTimer( defaultTimer ) ;
}

void Bomba::esplodi() {
    this -> attivo = false;
}

bool Bomba::aggiornaBomba() {

    if (innescata()) {

        diminuisciTimer() ;
        if (boostTimerAttivo( ))
            diminuisciTimer( ) ;
        if (getTimer() <= 0) {
            esplodi() ;
            return true ;
        }
    }

    aggiornaPotenziamenti( ) ;
    return false ;
}




void Bomba::attivaBoostDanno() {
    if ( !boostDannoAttivo()) {
        boostDanno = true;
        setDurataBoostDanno( defaultDurataBoostDanno );
        duplicaDanno();
    }
    else {
        setDurataBoostDanno( getDurataBoostDanno() + defaultDurataBoostDanno ) ;
    }
}

void Bomba::disattivaBoostDanno() {
    boostDanno = false;
    danno = defaultDanno ;
}

void Bomba::setDurataBoostDanno(int durata) {
    durataBoostDanno = durata;
}

void Bomba::diminuisciDurataBoostDanno() {
    if ( boostDannoAttivo() )
        durataBoostDanno -= 1 ;
}

int Bomba::getDurataBoostDanno() const {
    return durataBoostDanno;
}

bool Bomba::boostDannoAttivo() const {
    return boostDanno;
}

void Bomba::aggiornaBoostDanno() {
    if (boostDannoAttivo()) {
        diminuisciDurataBoostDanno();
        if (getDurataBoostDanno() <= 0)
            disattivaBoostDanno();
    }
}


void Bomba::attivaBoostRaggio() {
    if ( !boostRaggioAttivo()) {
        boostRaggio = true;
        setDurataBoostRaggio( defaultDurataBoostRaggio );
        raddoppiaRaggio();
    }
    else {
        setDurataBoostRaggio( getDurataBoosRaggio() + defaultDurataBoostRaggio) ;
    }
}

void Bomba::disattivaBoostRaggio() {
    boostRaggio = false;
    raggio = defaultRaggio ;
}
void Bomba::setDurataBoostRaggio(int durata) {
    durataBoostRaggio = durata;
}

void Bomba::diminuisciDurataBoostRaggio() {
    if ( boostRaggioAttivo() )
        durataBoostRaggio -= 1 ;
}

int Bomba::getDurataBoosRaggio() const {
    return durataBoostRaggio;
}

bool Bomba::boostRaggioAttivo() const{
    return boostRaggio;
}

void Bomba::aggiornaBoostRaggio() {
    if (boostRaggioAttivo()) {
        diminuisciDurataBoostRaggio();
        if (getDurataBoosRaggio() <= 0)
            disattivaBoostRaggio();
    }
}




void Bomba::attivaBoostTimer() {
    if ( !boostTimerAttivo()) {
        boostTimer = true;
        setDurataBoostTimer( defaultDurataBoostTimer);
    }
    else {
        setDurataBoostTimer( getDurataBoostTimer( ) + defaultDurataBoostTimer) ;
    }
}

void Bomba::disattivaBoostTimer() {
    boostTimer = false;
}

void Bomba::setDurataBoostTimer(int durata) {
    durataBoostTimer = durata;
}

void Bomba::diminuisciDurataBoostTimer() {
    durataBoostTimer-- ;
}


int Bomba::getDurataBoostTimer() const {
    return durataBoostTimer ;
}

bool Bomba::boostTimerAttivo() const{
    return boostTimer;
}

void Bomba::aggiornaBoostTimer() {
    if (boostTimerAttivo()) {
        diminuisciDurataBoostTimer();
        if (getDurataBoostTimer() <= 0)
            disattivaBoostTimer();
    }
}

void Bomba::aggiornaPotenziamenti( ) {
    aggiornaBoostTimer( ) ;
    aggiornaBoostRaggio( ) ;
    aggiornaBoostDanno( ) ;
}


void Bomba::disattivaPotenziamenti( ) {
    disattivaBoostDanno( ) ;
    disattivaBoostRaggio( ) ;
    disattivaBoostTimer( ) ;
}
