//
// Created by andre on 01/09/2026.
//

#include "Timer.h"

Timer::Timer(int tempo) {
    attivaTimer( tempo ) ;
}

int Timer::getTimer( ) {
    return this -> tempo  ;
}

void Timer::attivaTimer( int tempo ) {
    this -> tempo = tempo ;
}

void Timer::diminuisci(int tempo) {
    this -> tempo -= tempo ;
}

bool Timer::scaduto ( ) {
    return ( getTimer( ) <= 0 ) ;
}
