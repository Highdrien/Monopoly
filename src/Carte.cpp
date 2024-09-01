#include "Carte.h"
#include <iostream>

using namespace std;

Carte::Carte(){
    numero = 0;
    gain = 0;
    aller_a = -1;
    action_special = 0;
    texte = "carte vide";
}

Carte::Carte(int numero, int reculer_3cases, int gain, int liberer_prison, int reparation_1, int reparation_2, int aller_a, string texte){
    this->numero = numero;
    this->gain = gain;
    this->aller_a = aller_a;
    this->texte = texte;
    action_special = reculer_3cases + 2*liberer_prison + 3*reparation_1 + 4*reparation_2;

    if (numero == 17)
        action_special = 5;
}
