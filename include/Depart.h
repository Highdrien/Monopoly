#ifndef DEPART_H
#define DEPART_H

#include <Case.h>
#include "Joueur.h"

class Depart : public Case
{
    public:
        Depart(string nom);
        void arreterSur(Joueur*, bool);
};

#endif // DEPART_H
