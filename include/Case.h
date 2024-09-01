#ifndef CASE_H
#define CASE_H

#include "Joueur.h"

#include <iostream>
using namespace std;

class Case
{
    protected:
        string nom;     // nom de la case
        int numero;     // numero de la case
        bool color_mode;// nom des cases en couleur

    public:
        Case();
        Case(string nom, int numero);

        // Getteur
        string get_nom(){return nom;};
        int get_numero(){return numero;};

        // Setter
        void set_nom(string new_nom){nom = new_nom;};
        void set_color_mode(bool new_mode){color_mode = new_mode;};

        // virtual
        virtual void arreterSur(Joueur*, bool){cout << "Case vide" << endl;}; // Si on tombe sur la case

        virtual Joueur* get_proprietaire(){return NULL;};               // Récupère le proprietaire s'il existe
        virtual int get_nb_maison(){return 0;};                         // Récupère le nombre de maison s'il y en a
        virtual int get_prix_achat(){return 0;};                        // Récupère le prix d'achat
        virtual int get_prix_maison(){return 0;};                       // Récupère le prix d'achat d'une maison

        virtual void set_proprietaire(Joueur* joueur){};                // modifie le propriétaire de la case
        virtual void set_nb_maison(int new_nb_maisons){};               // modifie le nombre de maison de la case

        friend ostream& operator<<(ostream& out, Case&);
};

#endif // CASE_H
