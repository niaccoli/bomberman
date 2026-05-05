#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H


class Personaggio {
    protected:
        int vite;
        int x;
        int y;

    public:
        Personaggio();
        Personaggio(int vite, int x, int y);

        void setX(int x);
        void setY(int y);
        int getX () const;
        int getY () const;
        void muovi(int newx, int newy);


        void setVite(int vite);
        void aumentaVita();
        void diminuisciVita();
        bool vivo() const;
        int getVite() const;
};

#endif

