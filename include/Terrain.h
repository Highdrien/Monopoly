#ifndef TERRAIN_H
#define TERRAIN_H

#include <Propriete.h>


class Terrain : public Propriete
{
    private:
        int* loyer;         // tableau des loyers: [loyer simple, loyer avec 1 maison, ... ,loyer avec un hotel]
        int nb_maison;      // nombre de maison sur ce terrain (5 si il y a un hotel)
        int prix_maison;    // prix d'une maison
        Terrain** groupe;   // listes de pointeur vers les autres Terrain de la même famille

    public:
        Terrain();
        Terrain(string nom, int prix_achat,
                int numero, int loyer_simple,
                int loyer_maison1, int loyer_maison2,
                int loyer_maison3, int loyer_maison4,
                int loyer_hotel, int prix_maison);

        void achat_maisons(int nb_maisons_achetees){nb_maison = nb_maison + nb_maisons_achetees;};

        int joueur_possession(Joueur*);     // retourn le nombre de Terrain de la même famille que possède le joueur

        void arreterSur(Joueur*, bool);     // Si on tombe sur la case

        // Getteur
        int get_nb_maison(){return nb_maison;};
        int get_loyer(){return loyer[nb_maison];};  // retourne le loyer qu'il faut payer (en fonction du nombre de maison)
        int get_prix_maison(){return prix_maison;}; // Récupère le prix d'achat d'une maison

        // Setteur
        void setGroupe(Terrain*, Terrain*, Terrain*);   // crée une famille de Terrain (mettre NULL au troisème si la famille contient que 2 Terrains)
        void set_nb_maison(int new_nb_maisons){nb_maison = new_nb_maisons;};

};

#endif // TERRAIN_H
