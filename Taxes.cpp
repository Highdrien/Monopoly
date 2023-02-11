#include "Taxes.h"

#include <iostream>
using namespace std;

Taxes::Taxes():Case(){}

Taxes::Taxes(string nom, int numero, int taxes_a_payer):Case(nom, numero){
    this->taxes_a_payer = taxes_a_payer;
}

void Taxes::arreterSur(Joueur* joueur, bool fast_game){
    cout << "Vous devez payer: " << taxes_a_payer << " a la banque!" << endl;
    joueur->debiter(-taxes_a_payer);
}
