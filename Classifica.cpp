//
// Created by andre on 06/09/2026.
//

#include "Classifica.h"

#include <fstream>

#include "curses.h"

#include "cstring"
using namespace std ;

Classifica::Classifica( ) {
    head = nullptr ;
}

Classifica::pris Classifica::aggiungiRisultato_aux (pris r, char nome[],int punteggio) {
    if ( r == nullptr ) {
        pris temp = new risultato ;
        temp -> punteggio = punteggio ;
        strncpy( temp -> nome, nome, 99) ;
        temp -> nome[99] = '\0';
        temp -> next = nullptr ;
        return temp ;
    }

    if ( punteggio >= r -> punteggio ) {
        pris temp = new risultato ;
        temp -> punteggio = punteggio ;
        strncpy( temp -> nome, nome, 99) ;
        temp -> nome[99] = '\0';
        temp -> next = r ;
        return temp ;
    }

    else {
        r -> next = aggiungiRisultato_aux(r -> next, nome, punteggio ) ;
        return r ;
    }
}


void Classifica::aggiungiRisultato(char nome[], int punteggio) {
    head = aggiungiRisultato_aux( head, nome, punteggio ) ;
}

void Classifica::caricaDaFile() {
    ifstream inputFile;
    inputFile.open("Classifica.txt");

    char nome[100];
    int punteggio;

    while ( inputFile >> nome >> punteggio) {

        aggiungiRisultato(nome, punteggio);

    }

    inputFile.close();
}


void Classifica::caricaDaFile_v2() {
    ifstream inputFile;
    inputFile.open("Classifica.txt");

    char nome[100];
    int punteggio;

    while (inputFile.getline(nome, 100, ';') && inputFile >> punteggio) { //getline(..., ';')legge tutto fino al ;
        aggiungiRisultato(nome, punteggio);
        inputFile.ignore(); //scarta il '\n' rimasto dopo il punteggio
    }


    inputFile.close();
}


void Classifica::salvaSuFile( ) {
    ofstream outputFile ;
    outputFile.open("Classifica.txt") ;

    pris temp = head  ;

    while ( temp != nullptr ) {
        outputFile << temp -> nome ;
        outputFile << ' ' ;
        outputFile << temp -> punteggio ;
        outputFile << '\n' ;
        temp = temp -> next ;
    }

    outputFile.close() ;

}



void Classifica::salvaSuFile_v2( ) {
    ofstream outputFile ;
    outputFile.open("Classifica.txt") ;

    pris temp = head  ;

    while ( temp != nullptr ) {
        outputFile << temp -> nome ;
        outputFile << ';' ;
        outputFile << temp -> punteggio ;
        outputFile << '\n' ;
        temp = temp -> next ;
    }

    outputFile.close() ;
}

void Classifica::mostraMigliori(int n) {

    clear();

    mvprintw(1, 1, "CLASSIFICA");

    pris temp = head;
    int posizione = 1;
    int y = 3;

    while (temp != nullptr && posizione <= n) {

        mvprintw(
            y,
            1,
            "%d. %s - %d",
            posizione,
            temp->nome,
            temp->punteggio
        );

        temp = temp->next;
        posizione++;
        y++;
    }

    if (head == nullptr)
        mvprintw(3, 1, "Nessun risultato presente");

    mvprintw(y + 2, 1, "Premi INVIO per tornare al menu");

    refresh();

    timeout(-1);

    int input = getch();

    while (input != '\n')
        input = getch();

    clear();
    refresh();
}
