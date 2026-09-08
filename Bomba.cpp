#include "Bomba.h"

Bomba::Bomba():
posizione{ -1, -1 },
timer(0), potenziamentoTimer(false), durataPotenziamentoTimer(0),
raggio(defaultRaggio), potenziamentoRaggio(false), durataPotenziamentoRaggio(0),
attivo(false), appenaInnescata(false),
danno(defaultDanno), potenziamentoDanno(false), durataPotenziamentoDanno(0)
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

            if (potenziamentoTimerAttivo())
                diminuisciTimer(durata);
        }

        if (getTimer() <= 0) {
            esplodi();
            return true;
        }
    }
    return false ;
}



void Bomba::attivaPotenziamentoDanno() {
    if ( !potenziamentoDannoAttivo()) {
        potenziamentoDanno = true;
        setDurataPotenziamentoDanno( durataDefaultPotenziamentoDanno );
        duplicaDanno();
    }
    else {
        setDurataPotenziamentoDanno( getDurataPotenziamentoDanno() + durataDefaultPotenziamentoDanno ) ;
    }
}

void Bomba::disattivaPotenziamentoDanno() {
    potenziamentoDanno = false;
    danno = defaultDanno ;
}

void Bomba::setDurataPotenziamentoDanno(int durata) {
    durataPotenziamentoDanno = durata;
}

void Bomba::diminuisciDurataPotenziamentoDanno(int durata) {
    if ( potenziamentoDannoAttivo() )
        durataPotenziamentoDanno -= durata ;
}

int Bomba::getDurataPotenziamentoDanno() const {
    return durataPotenziamentoDanno;
}

bool Bomba::potenziamentoDannoAttivo() const {
    return potenziamentoDanno;
}


void Bomba::aggiornaPotenziamentoDanno(int durata) {
    if (potenziamentoDannoAttivo()) {
        diminuisciDurataPotenziamentoDanno(durata);
        if (getDurataPotenziamentoDanno() <= 0)
            disattivaPotenziamentoDanno();
    }
}


void Bomba::attivaPotenziamentoRaggio() {
    if ( !potenziamentoRaggioAttivo()) {
        potenziamentoRaggio = true;
        setDurataPotenziamentoRaggio( durataDefaultPotenziamentoRaggio );
        raddoppiaRaggio();
    }
    else {
        setDurataPotenziamentoRaggio( getDurataPotenziamentoRaggio() + durataDefaultPotenziamentoRaggio) ;
    }
}

void Bomba::disattivaPotenziamentoRaggio() {
    potenziamentoRaggio = false;
    raggio = defaultRaggio ;
}
void Bomba::setDurataPotenziamentoRaggio(int durata) {
    durataPotenziamentoRaggio = durata;
}

void Bomba::diminuisciDurataPotenziamentoRaggio(int durata) {
    if ( potenziamentoRaggioAttivo() )
        durataPotenziamentoRaggio -= durata ;
}

int Bomba::getDurataPotenziamentoRaggio() const {
    return durataPotenziamentoRaggio;
}

bool Bomba::potenziamentoRaggioAttivo() const{
    return potenziamentoRaggio;
}


void Bomba::aggiornaPotenziamentoRaggio(int durata) {
    if (potenziamentoRaggioAttivo()) {
        diminuisciDurataPotenziamentoRaggio(durata);
        if (getDurataPotenziamentoRaggio() <= 0)
            disattivaPotenziamentoRaggio();
    }
}


void Bomba::attivaPotenziamentoTimer() {
    if ( !potenziamentoTimerAttivo()) {
        potenziamentoTimer = true;
        setDurataPotenziamentoTimer( durataDefaultPotenziamentoTimer);
    }
    else {
        setDurataPotenziamentoTimer( getDurataPotenziamentoTimer( ) + durataDefaultPotenziamentoTimer) ;
    }
}

void Bomba::disattivaPotenziamentoTimer() {
    potenziamentoTimer = false;
}

void Bomba::setDurataPotenziamentoTimer(int durata) {
    durataPotenziamentoTimer = durata;
}

void Bomba::diminuisciDurataPotenziamentoTimer( int durata ) {
    durataPotenziamentoTimer -= durata ;
}

int Bomba::getDurataPotenziamentoTimer() const {
    return durataPotenziamentoTimer ;
}

bool Bomba::potenziamentoTimerAttivo() const{
    return potenziamentoTimer;
}

void Bomba::aggiornaPotenziamentoTimer(int durata ) {
    if (potenziamentoTimerAttivo()) {
        diminuisciDurataPotenziamentoTimer(durata);
        if (getDurataPotenziamentoTimer() <= 0)
            disattivaPotenziamentoTimer();
    }
}


void Bomba::aggiornaPotenziamenti(int durata ) {
    aggiornaPotenziamentoTimer(durata ) ;
    aggiornaPotenziamentoRaggio(durata ) ;
    aggiornaPotenziamentoDanno(durata ) ;
}

void Bomba::disattivaPotenziamenti( ) {
    disattivaPotenziamentoDanno( ) ;
    disattivaPotenziamentoRaggio( ) ;
    disattivaPotenziamentoTimer( ) ;
}
