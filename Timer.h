//
// Created by andre on 01/09/2026.
//

#ifndef BOMBERMAN_TIMER_H
#define BOMBERMAN_TIMER_H


class Timer {
protected:
    int tempo ; //unita': ms

public:
    Timer(int tempo) ;
    int getTimer( ) ;
    void attivaTimer( int tempo ) ;
    void diminuisci(int tempo) ;
    bool scaduto ( ) ;


};


#endif //BOMBERMAN_TIMER_H