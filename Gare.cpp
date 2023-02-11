#include "Gare.h"

#include <iostream>
using namespace std;

Gare::Gare():Propriete(){}

Gare::Gare(string nom, int numero, int loyer, int prix_achat):Propriete(nom, numero, loyer, prix_achat){}

void Gare::arreterSur(Joueur* joueur, bool fast_game){
    // Si la gare est à personne
    if (proprietaire == NULL || proprietaire->est_en_vie() == false){
        cout << "La Gare n'appartient a personne. Vous avez " << joueur->get_solde() << " et la gare coute " << prix_achat <<".";
        cout << " Vous avez " << joueur->get_nb_gares() << " gare(s)." << endl;
        // On regarde si le joueur a assez d'argent
        if (joueur->get_solde() > prix_achat){
            cout << "Voulez-vous vous l'acheter? " << endl;
            string reponse = "init";

            while(reponse != "oui" && reponse != "OUI" && reponse != "Oui" && reponse != "non" && reponse != "Non" && reponse != "NON"){
                if (fast_game)
                    reponse = "Oui";
                else
                    cin >> reponse;

                if(reponse == "oui" || reponse == "OUI" || reponse == "Oui"){
                    cout << "La " << nom << " est a vous" << endl;
                    proprietaire = joueur;
                    joueur->debiter(-prix_achat);
                    joueur->add_nb_gares();

                }else if(reponse == "non" || reponse == "NON" || reponse == "Non"){
                    cout << "Tant pis" << endl;

                }else{
                    cout << "Veuillez repondre pas oui ou par non"<< endl;
                }
            }
        }
        else cout << "Vous n'avez pas assez d'argent pour l'achetter!" << endl;
    }
    // Si la gare est au joueur actif
    else if (proprietaire == joueur){
        cout << "Cette gare est a vous" << endl;
    }
    // Si la gare est à un autre joueur
    else{
        cout << "Cette gare est a " << proprietaire->get_nom() <<". Il possede " << proprietaire->get_nb_gares() << " gare(s)." << endl;

        int prix = 25 * proprietaire->get_nb_gares();        // s'il en possede 1 ou 2
        if (proprietaire->get_nb_gares() > 2)
            prix = 100 * (proprietaire->get_nb_gares() - 2); // s'il en possede 3 ou 4

        cout << "Vous devez lui payer " << prix << endl;
        proprietaire->debiter(prix);
        joueur->debiter(-prix);
    }
}
