#ifndef CHANCE_H
#define CHANCE_H

#include <Case.h>
#include "ListCarte.h"
#include "Carte.h"


class Chance : public Case
{
    private:
        ListCarte cartes;           // liste des cartes chances (et caisse de communaute)

    public:
        Chance();
        Chance(string nom, int numero);

        void arreterSur(Joueur*, bool);   // Si on tombe sur la case
};

#endif // CHANCE_H
