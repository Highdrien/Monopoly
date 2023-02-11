#ifndef COMMUNAUTE_H
#define COMMUNAUTE_H

#include <Case.h>
#include "ListCarte.h"
#include "Carte.h"


class Communaute : public Case
{
    private:
        ListCarte cartes;           // liste des cartes caises de communaute (et chances)

    public:
        Communaute();
        Communaute(string nom, int numero);

        void arreterSur(Joueur*, bool);
};

#endif // COMMUNAUTE_H
