#ifndef LISTCARTE_H
#define LISTCARTE_H
#include "Carte.h"


class ListCarte
{
    private:
        Carte* liste_carte_chance;      // Liste des cartes chance
        Carte* liste_carte_communaute;  // Liste des cartes caisse de communaute

    public:
        ListCarte();
        Carte get_carte_chance(int);        // récupère une carte chance
        Carte get_carte_communautte(int);   // récupère une carte de communaute
};

#endif // LISTCARTE_H
