//
// Created by andre on 06/09/2026.
//

#include "Classifica.h"

#include <fstream>

#include "curses.h"

#include <cstdlib>

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

    while (inputFile.getline(nome, 100, ';') && inputFile >> punteggio) {
        aggiungiRisultato(nome, punteggio);
        inputFile.ignore();
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


void Classifica::stampaClassifica( ) {
    bool fine = false;

    while (!fine) {

        char numero[10];

        clear();

        mvprintw(1, 1, "Quanti risultati vuoi visualizzare? (Invio = 10)");

        echo();
        curs_set(1);
        refresh();

        getnstr(numero, 9);

        noecho();
        curs_set(0);

        int n;

        int i = 0;

        while (numero[i] == ' ')
            i++;


        if (numero[i] == '\0') {
            n = 10;
        }

        else {

            bool valido = true;
            int inizioNumero = i;

            while (numero[i] != '\0' && valido) {

                if (numero[i] < '0' || numero[i] > '9')
                    valido = false;

                i++;
            }

            if (valido)
                n = atoi(numero + inizioNumero);
            else
                n = -1;
        }


        if (n != -1) {

            mostraMigliori(n);
            fine = true;

        }

        else {

            clear();

            mvprintw(1, 1, "Input non valido.");
            mvprintw(3, 1, "Riprovare? [Y/N]");
            refresh();

            int input = getch();

            while (input != 'y' &&
                   input != 'Y' &&
                   input != 'n' &&
                   input != 'N') {

                input = getch();
                   }


            if (input == 'n' || input == 'N')
                fine = true;
        }
    }
}
