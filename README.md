# Bomberman - Clone in C++ con ncurses

Un clone del classico videogioco arcade *Bomberman*, interamente sviluppato in C++ ed eseguibile da terminale grazie alla libreria grafica `ncurses`.

## 👥 Membri del Gruppo
Come richiesto dalle specifiche di consegna, ecco i riferimenti dei membri del team:

* **Mat** 
  * Matricola: 
  * Email: [tua.email@studio.unibo.it]
* **[Nome Cognome Compagno]**
  * Matricola: [Numero Matricola]
  * Email: [email.compagno@studio.unibo.it]

---

## 🎮 Features Principali
* **Esplorazione Bidirezionale (Dungeon Crawler):** I livelli sono collegati tramite una lista doppiamente concatenata. È possibile avanzare (tramite le porte `U`) o fare backtracking (tramite le porte `@`) mantenendo in memoria lo stato delle mappe.
* **Level Design Dinamico:** Le mappe sono caricate dinamicamente da file `.txt`, facilitando la creazione e la scalabilità del gioco.
* **Heads-Up Display (HUD):** Un pannello laterale fornisce feedback in tempo reale su Vite, Tempo rimanente (formato MM:SS), Punteggio e tracciamento della durata dei Potenziamenti.
* **Potenziamenti (Item):** 
  * Boost Danno
  * Boost Raggio Esplosione
  * Boost Timer (Bomba Veloce)
* **Intelligenza Artificiale Nemici:** Diverse tipologie di nemici (Inseguitori, Veloci, Corazzati) per garantire un livello di sfida crescente.

---

## 🛠 Prerequisiti e Dipendenze
Per compilare ed eseguire il gioco è necessario un ambiente Unix-like (Linux/macOS) con i seguenti pacchetti installati:
* Compilatore C++ (es. `g++` o `clang++` con supporto C++11 o superiore)
* CMake (versione 3.10+)
* Libreria grafica **ncurses**

**Installazione dipendenze (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install build-essential cmake libncurses5-dev libncursesw5-dev