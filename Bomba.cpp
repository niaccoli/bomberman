#include "Bomba.h"

Bomba::Bomba():
posizione{ -1, -1 },
timer(0), boostTimer(false), durataBoostTimer(0),
raggio(defaultRaggio), boostRaggio(false), durataBoostRaggio(0),
attivo(false), appenaInnescata(false),
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

void Bomba::diminuisciTimer(int durata) {
    this -> timer -= durata ;
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
    appenaInnescata = true ;
}

void Bomba::esplodi() {
    this -> attivo = false;
    appenaInnescata = false ;
}


bool Bomba::aggiornaBomba(int durata) {

    if (innescata()) {

        if (appenaInnescata) {
            appenaInnescata = false;
        }
        else {
            diminuisciTimer(durata);

            if (boostTimerAttivo())
                diminuisciTimer(durata);
        }

        if (getTimer() <= 0) {
            esplodi();
            return true;
        }
    }
    return false ;
}



void Bomba::attivaBoostDanno() {
    if ( !boostDannoAttivo()) {
        boostDanno = true;
        setDurataBoostDanno( durataDefaultPotenziamentoDanno );
        duplicaDanno();
    }
    else {
        setDurataBoostDanno( getDurataBoostDanno() + durataDefaultPotenziamentoDanno ) ;
    }
}

void Bomba::disattivaBoostDanno() {
    boostDanno = false;
    danno = defaultDanno ;
}

void Bomba::setDurataBoostDanno(int durata) {
    durataBoostDanno = durata;
}

void Bomba::diminuisciDurataBoostDanno(int durata) {
    if ( boostDannoAttivo() )
        durataBoostDanno -= durata ;
}

int Bomba::getDurataBoostDanno() const {
    return durataBoostDanno;
}

bool Bomba::boostDannoAttivo() const {
    return boostDanno;
}


void Bomba::aggiornaBoostDanno(int durata) {
    if (boostDannoAttivo()) {
        diminuisciDurataBoostDanno(durata);
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

void Bomba::diminuisciDurataBoostRaggio(int durata) {
    if ( boostRaggioAttivo() )
        durataBoostRaggio -= durata ;
}

int Bomba::getDurataBoosRaggio() const {
    return durataBoostRaggio;
}

bool Bomba::boostRaggioAttivo() const{
    return boostRaggio;
}


void Bomba::aggiornaBoostRaggio(int durata) {
    if (boostRaggioAttivo()) {
        diminuisciDurataBoostRaggio(durata);
        if (getDurataBoosRaggio() <= 0)
            disattivaBoostRaggio();
    }
}


void Bomba::attivaBoostTimer() {
    if ( !boostTimerAttivo()) {
        boostTimer = true;
        setDurataBoostTimer( durataDefaultPotenziamentoTimer);
    }
    else {
        setDurataBoostTimer( getDurataBoostTimer( ) + durataDefaultPotenziamentoTimer) ;
    }
}

void Bomba::disattivaBoostTimer() {
    boostTimer = false;
}

void Bomba::setDurataBoostTimer(int durata) {
    durataBoostTimer = durata;
}

void Bomba::diminuisciDurataBoostTimer( int durata ) {
    durataBoostTimer -= durata ;
}

int Bomba::getDurataBoostTimer() const {
    return durataBoostTimer ;
}

bool Bomba::boostTimerAttivo() const{
    return boostTimer;
}

void Bomba::aggiornaBoostTimer(int durata ) {
    if (boostTimerAttivo()) {
        diminuisciDurataBoostTimer(durata);
        if (getDurataBoostTimer() <= 0)
            disattivaBoostTimer();
    }
}


void Bomba::aggiornaPotenziamenti(int durata ) {
    aggiornaBoostTimer(durata ) ;
    aggiornaBoostRaggio(durata ) ;
    aggiornaBoostDanno(durata ) ;
}

void Bomba::disattivaPotenziamenti( ) {
    disattivaBoostDanno( ) ;
    disattivaBoostRaggio( ) ;
    disattivaBoostTimer( ) ;
}
