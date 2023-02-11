#include "Des.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

Des::Des(){
    valeur_de1 = 0;
    valeur_de2 = 0;
    meme_valeur = false;
}

int Des::lancer(){
    //sleep_for(1000ms);
    //srand((unsigned int)time(0));
    valeur_de1 = rand()%6 + 1;

    //sleep_for(1000ms);
    valeur_de2 = rand()%6 + 1;

    meme_valeur = (valeur_de1 == valeur_de2);

    return valeur_de1 + valeur_de2;
}
