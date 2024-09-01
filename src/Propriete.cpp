#include "Propriete.h"

Propriete::Propriete(){
    loyer = 0;
    prix_achat = 0;
    proprietaire = NULL;
}

Propriete::Propriete(string nom, int numero, int loyer, int prix_achat):Case(nom, numero){
    this->loyer = loyer;
    this->prix_achat = prix_achat;
    proprietaire = NULL;
}
