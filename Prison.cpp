#include "Prison.h"

#include <iostream>
using namespace std;

Prison::Prison():Case(){}

Prison::Prison(string nom, int numero):Case(nom, numero){}

void Prison::arreterSur(Joueur* joueur, bool fast_game){
    // 2 cases Prison: la case 10 (la prision) et la case 30 (la case allez en prison)

    if (numero == 10){
        cout << "Vous etes en simple visite, profitez bien" << endl;
    }

    if (numero == 30){
        cout << "On vous embarque en prison!" << endl;
        joueur->set_prison(true);
        joueur->set_position(10);

        // On regarte s'il a une carte de sortie de prison et si il veux l'utiliser
        if (joueur->get_carte_sortie_prison()){
            cout << "Vous avez une carte sortie de prison. Voulez-vous l'utiliser ?";
            string reponse = "init";

            while(reponse != "oui" && reponse != "non"){
                cin >> reponse;

                if(reponse == "oui"){
                    joueur->set_prison(false);              // On le sort de prison
                    joueur->set_carte_sortie_prison(false); // On lui enlève sa carte de sortie de prison
                }
                else if(reponse != "non"){
                    cout << "Veuillez repondre pas oui ou par non"<< endl;
                }
            }
        }

    }
}
