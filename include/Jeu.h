#ifndef JEU_H
#define JEU_H

#include "Joueur.h"
#include "ListCarte.h"
#include "Des.h"
#include "Plateau.h"

#include <iostream>
using namespace std;

class Jeu
{
    private:
        Plateau plateau;        // plateau du monopoly
        int nb_joueurs;         // nombre de joueur
        Joueur* list_joueurs;   // listes des joueurs
        int tour_de_jeu;        // nombre de tour de jeu
        int joueur_actif;       // indice du joueur qui est ne train de jouer
        Des d;                  // dé
        bool game_on;           // pour savoir si la parie est en cours
        int numero_partie;      // numero de la partie
        bool fast_game;         // partie rapide
        bool color_mode;        // texte ecrit en couleur ou non

    public:
        Jeu(int, int, bool, bool);    // crée une partie avec le nb de joueur, le numéro de partie,
                                      // si c'est une partie rapide ou non, et si c'est un mode couleur ou non
        void create_joueur(int, string);    // crée un joueur
        void affiche_joueurs();             // affiche le statut des joueurs
        void affiche_possession(Joueur*);   // affiche la liste des possessions d'un joueur

        void jouer(Joueur*);    // fait jouer le joueur
        void tour();            // fait un tour
        void game();            // lancer le jeu

        int compte_joueur_en_vie(); // compte le nombre de joueur encore en vie
        void check_joueur(Joueur*); // regarde si le joueur est en négatif, si c'est le cas, vend ses maisons/hotels propriétés
        void trade();               // fait des échanges de cartes entre les joueurs
        int numero_joueur(string);  // renvoie l'indice du joueur en ayant son nom (renvoie -1 si le joueur n'éxiste pas)

        void saving_game();     // sauvegarde la partie en cours
        void loading_game(int); // chargement d'une partie sauvegardée
};

#endif // JEU_H
