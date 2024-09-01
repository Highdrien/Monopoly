#ifndef PARC_H
#define PARC_H

#include <Case.h>
#include "Joueur.h"

#include <iostream>
using namespace std;

class Parc : public Case
{
    public:
        Parc(string nom);
        void arreterSur(Joueur*, bool){cout << "Vous vous la coulez douce au Parc." << endl;};
};

#endif // PARC_H
