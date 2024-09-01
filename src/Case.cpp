#include "Case.h"

Case::Case(){
    nom = "";
    numero = -1;
    color_mode = false;
}


Case::Case(string nom, int numero){
    this->nom = nom;
    this->numero = numero;
    color_mode = false;
}

ostream& operator<<(ostream& out, Case& c){
    out << c.nom;
    return out;
}
