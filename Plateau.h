#ifndef PLATEAU_H
#define PLATEAU_H

#include "Case.h"

class Plateau
{
    private:
        Case** liste_cases;  // liste de pointeur vers les cases

    public:
        Plateau();
        void color_mode();   // mets des couleurs sur le nom des cases
        Case* get_cases(int i){return liste_cases[i];};

        Case* operator[](int);  // surgarge d'opérateur
};

#endif // PLATEAU_H
