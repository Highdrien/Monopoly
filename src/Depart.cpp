#include "Depart.h"

#include <iostream>
using namespace std;

Depart::Depart(string nom):Case(nom, 0){}

void Depart::arreterSur(Joueur* joueur, bool fast_game){
    cout << "Reposez-vous sur la ligne de depart" << endl;
}
