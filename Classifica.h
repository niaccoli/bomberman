//
// Created by andre on 06/09/2026.
//

#ifndef BOMBERMAN_CLASSIFICA_H
#define BOMBERMAN_CLASSIFICA_H


class Classifica {
protected:
    // Rappresenta un risultato salvato nella classifica.
    struct risultato {
        char nome[100] ;
        int punteggio ;
        risultato* next ;
    };
    typedef risultato* pris ;

    pris head ;

    // Inserisce ricorsivamente un risultato nella posizione corretta,
    // mantenendo la classifica ordinata per punteggio decrescente.
    pris aggiungiRisultato_aux (pris r, char nome[],int punteggio) ;

public :
    // Crea una classifica inizialmente vuota.
    Classifica( ) ;

    // Aggiunge un nuovo risultato alla classifica,
    // mantenendo i risultati ordinati per punteggio decrescente.
    void aggiungiRisultato(char nome[],int punteggio) ;

    // Carica i risultati dal file "Classifica.txt".
    // Il formato previsto per ogni riga è: nome punteggio
    void caricaDaFile( ) ;

    // Carica i risultati dal file "Classifica.txt".
    // Il formato previsto per ogni riga è: nome;punteggio.
    // Permette quindi di utilizzare nomi contenenti spazi.
    void caricaDaFile_v2( ) ;

    // Salva tutti i risultati nel file "Classifica.txt".
    // Il formato utilizzato è: nome punteggio.
    void salvaSuFile( ) ;

    // Salva tutti i risultati nel file "Classifica.txt".
    // Il formato utilizzato è: nome;punteggio.
    void salvaSuFile_v2( ) ;

    // Mostra a schermo i primi n risultati della classifica
    // e attende la pressione di INVIO prima di tornare al menu.
    void mostraMigliori(int n) ;

    // Chiede all'utente quanti risultati visualizzare.
    // Se viene premuto INVIO senza inserire un numero, mostra i primi 10.
    // Gestisce inoltre eventuali input non validi.
    void stampaClassifica( ) ;
};


#endif //BOMBERMAN_CLASSIFICA_H