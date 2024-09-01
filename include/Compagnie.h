#ifndef COMPAGNIE_H
#define COMPAGNIE_H

#include <Propriete.h>
#include "Des.h"


class Compagnie : public Propriete
{
    private:
        Des d;      // des (car le loyer dépend du lanceé des des)

    public:
        Compagnie();
        Compagnie(string nom, int numero, int loyer, int prix_achat);

        void arreterSur(Joueur*, bool);   // Si on tombe sur la case
};

#endif // COMPAGNIE_H
