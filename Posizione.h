//
// Created by andre on 14/08/2026.
//

#ifndef BOMBERMAN_POSIZIONE_H
#define BOMBERMAN_POSIZIONE_H

struct Posizione {
    int x ;
    int y ;
};

bool stessaPosizione(Posizione p1, Posizione p2) ;

double distanza (Posizione p1, Posizione p2) ;

#endif //BOMBERMAN_POSIZIONE_H