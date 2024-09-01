#include "Joueur.h"

#include <iostream>
using namespace std;


Joueur::Joueur(){
    nom = "joueur";
    solde = 1500;
    position = 0;
    en_vie = true;
    en_prison = 0;
    carte_prison = false;
    nb_gares = 0;
    nb_compagnies = 0;
}

void Joueur::avance(int i){
    position = (position + i)%40;
}

void Joueur::debiter(int gain){
    solde = solde + gain;
    cout << "Le solde de " << nom << " a ete mis a jour, vous avez: " << solde << endl;
}

void Joueur::status(){
    if (en_vie){
        cout << "--- Joueur: " << nom << " ---" <<endl;
        cout << "solde: " << solde << endl;
        cout << "position: " << position << endl;
    }
    else
        cout << "le joueur " << nom << " n'est plus dans la partie" << endl;

}

void Joueur::reduit_peine_prison(){
    if (en_prison > 0)
        en_prison = en_prison -1;
}

void Joueur::add_nb_gares(){
    nb_gares++;
}

void Joueur::add_nb_compagnies(){
    nb_compagnies++;
}

// Setteur
void Joueur::set_prison(bool prison){
    if (prison){
        position = 10;
    }
    en_prison = prison * 3;
}
