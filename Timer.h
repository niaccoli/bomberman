//
// Created by andre on 01/09/2026.
//

#ifndef BOMBERMAN_TIMER_H
#define BOMBERMAN_TIMER_H


class Timer {
protected:
    int tempo ;

public:
    Timer(int tempo) ;
    int getTimer( ) ;
    void setTimer( int tempo ) ;
    bool scaduto ( ) ;


};


#endif //BOMBERMAN_TIMER_H