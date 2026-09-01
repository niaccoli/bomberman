#include "Posizione.h"
#include <cmath>

bool stessaPosizione(Posizione p1, Posizione p2) {
    return ( ( p1.x == p2.x ) && ( p1.y == p2.y ) ) ;
}

double distanza(Posizione p1, Posizione p2) {
    return ( sqrt (pow(static_cast<double> (p1.x) , static_cast<double> ( p2.x)) +
        pow(static_cast<double> (p1.y) , static_cast<double> ( p2.y)))) ;
}
