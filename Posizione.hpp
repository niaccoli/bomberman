#ifndef BOMBERMAN_POSIZIONE_H
#define BOMBERMAN_POSIZIONE_H

// Rappresenta una posizione bidimensionale tramite
// le coordinate intere x e y.
struct Posizione {
    int x ;
    int y ;
};

// Restituisce true se le due posizioni hanno
// le stesse coordinate x e y, false altrimenti.
bool stessaPosizione(Posizione p1, Posizione p2) ;



#endif //BOMBERMAN_POSIZIONE_H