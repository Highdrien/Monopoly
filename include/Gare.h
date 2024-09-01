#ifndef GARE_H
#define GARE_H

#include <Propriete.h>


class Gare : public Propriete
{
    public:
        Gare();
        Gare(string nom, int numero, int loyer, int prix_achat);

        void arreterSur(Joueur*, bool);   // Si on tombe sur la case
};

#endif // GARE_H
