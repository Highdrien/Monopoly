#include "Compagnie.h"

#include <iostream>
using namespace std;

Compagnie::Compagnie():Propriete(){
    d = Des();
}

Compagnie::Compagnie(string nom, int numero, int loyer, int prix_achat):Propriete(nom, numero, loyer, prix_achat){}

void Compagnie::arreterSur(Joueur* joueur, bool fast_game){
    // Si la compagnie est à personne
    if (proprietaire == NULL || proprietaire->est_en_vie() == false){
        cout << "La Compagnie n'appartient a personne. Vous avez " << joueur->get_solde() << " et la compagnie coute " << prix_achat <<".";
        cout << " Vous avez " << joueur->get_nb_compagnies() << " compagnie(s)." << endl;
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
                    joueur->add_nb_compagnies();

                }else if(reponse == "non" || reponse == "NON" || reponse == "Non"){
                    cout << "Tant pis" << endl;

                }else{
                    cout << "Veuillez repondre pas oui ou par non"<< endl;
                }
            }
        }
        else cout << "Vous n'avez pas assez d'argent pour l'achetter!" << endl;
    }
    // Si la compagnie est au joueur actif
    else if (proprietaire == joueur){
        cout << "Cette compagnie est a vous" << endl;
    }

    // Si la compagnie est à un autre joueur
    else{
        cout << "Cette compagnie est a " << proprietaire->get_nom() <<". Il possede " << proprietaire->get_nb_compagnies() << " compagnie(s)." << endl;
        cout << "Lancer les des pour savoir combien vous devez payer." << endl;
        d.lancer();
        int prix = 4 * d.get_valeur();
        if (proprietaire->get_nb_compagnies() == 2)
            prix = 10 * d.get_valeur();
        cout << "Vous avez fait: " << d.get_valeur() << ". Vous devez donc: " << prix << " a " << proprietaire->get_nom() << "!" << endl;
        proprietaire->debiter(prix);
        joueur->debiter(-prix);
    }
}
