#ifndef PROPRIETE_H
#define PROPRIETE_H

#include <Case.h>
#include "Joueur.h"


class Propriete : public Case
{
    protected:
        int loyer;       // loyer de la propri�t�
        int prix_achat;  // prix de l'accisition de la propri�t�

        Joueur* proprietaire;  /* pointeur Joueur qui poss�de la propri�t�,
                                    si personne ne poss�de la propri�t� proprietaire=NULL */


    public:
        Propriete();
        Propriete(string nom, int numero, int loyer, int prix_achat);

        // Getteur
        int get_loyer(){return loyer;};
        int get_prix_achat(){return prix_achat;};
        Joueur* get_proprietaire(){return proprietaire;};

        // Setteur
        void set_loyer(int new_loyer){loyer = new_loyer;};
        void set_proprietaire(Joueur* new_proprietaire){proprietaire = new_proprietaire;};
};

#endif // PROPRIETE_H
