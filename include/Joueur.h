#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
using namespace std;

class Joueur
{
    private:
        string nom;     // nom du joueur
        int solde;      // solde du joueur
        int position;   // position du joueur
        bool en_vie;    // booléen pour savoir si le joueur est toujours de la partie
        int en_prison;  // pour savoir s'il est en prison (0=libre, 1=plus qu'un tour en prison, 2=plus que 2 tours en prison, 3plus que 3 tours en prison)
        bool carte_prison;      // est ce que le joueur à une carte de sortie de prison
        int nb_gares;           // nombre de gare(s) que le joueur possède
        int nb_compagnies;      // nombre de companie(s) que le joueur possède
        int nb_maisons;         // nombre de maisons que possède le joueur
        int nb_hotels;          // nombre d'hotel que possède le joueur
        int numero_joueur;      // numero du joueur (sert pour la sauvegarde des parties)

    public:
        Joueur();

        void avance(int i);     // new_position = position + i
        void debiter(int gain); // nouveau_solde = ancien_solde + gain
                                //      si le nouveau solde devient négatif, envie passe à false
        void status();          // affiche les infos du joueur

        void reduit_peine_prison(); // reduit la peine de 1 tour de prison
        void add_nb_gares();        // ajoute une gare
        void add_nb_compagnies();   // ajoute une compagnie

        // Getteur
        string get_nom(){return nom;};
        int get_solde(){return solde;};
        int get_position(){return position;};
        bool est_en_vie(){return en_vie;};
        int get_en_prison(){return en_prison;};
        bool get_carte_sortie_prison(){return carte_prison;};
        int get_nb_gares(){return nb_gares;};
        int get_nb_compagnies(){return nb_compagnies;};
        int get_nb_maisons(){return nb_maisons;};
        int get_nb_hotels(){return nb_hotels;};
        int get_numero_joueur(){return numero_joueur;};

        // Setteur
        void set_nom(string new_nom){nom = new_nom;};
        void set_solde(int new_solde){solde = new_solde;};
        void set_position(int new_position){position = new_position%40;};
        void set_en_vie(bool vivant){en_vie = vivant;};
        void set_prison(bool);
        void set_en_prison(int est_en_prison){en_prison = est_en_prison;};
        void set_carte_sortie_prison(bool a_une_carte){carte_prison = a_une_carte;};
        void set_nb_gares(int new_nb_gares){nb_gares = new_nb_gares;};
        void set_nb_compagnies(int new_nb_compagnies){nb_compagnies = new_nb_compagnies;};
        void set_nb_maisons(int new_nb_maisons){nb_maisons = new_nb_maisons;};
        void set_nb_hotels(int new_nb_hotels){nb_hotels = new_nb_hotels;};
        void set_numero_joueur(int new_numero_joueur){numero_joueur = new_numero_joueur;};
};

#endif // JOUEUR_H
