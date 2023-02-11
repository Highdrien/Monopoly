#include "Terrain.h"

#include <iostream>
using namespace std;

Terrain::Terrain():Propriete(){
    loyer = new int[6];
    nb_maison = 0;
    groupe = new Terrain*[3];
}

Terrain::Terrain(string nom, int prix_achat, int numero, int loyer_simple, int loyer_maison1, int loyer_maison2, int loyer_maison3, int loyer_maison4, int loyer_hotel, int prix_maison)
    :Propriete(nom, numero, loyer_simple, prix_achat)
{
    loyer = new int[6];
    loyer[0] = loyer_simple;
    loyer[1] = loyer_maison1;
    loyer[2] = loyer_maison2;
    loyer[3] = loyer_maison3;
    loyer[4] = loyer_maison4;
    loyer[5] = loyer_hotel;

    nb_maison = 0;
    this->prix_maison = prix_maison;
    groupe = new Terrain*[3];
}

void Terrain::setGroupe(Terrain* t0, Terrain* t1, Terrain* t2){
    groupe[0] = t0;
    groupe[1] = t1;
    groupe[2] = t2;
}

int Terrain::joueur_possession(Joueur* joueur){
    int nb_terrain = 0;

    for (int i=0; i<3; i++){
        if (groupe[i] != NULL && groupe[i]->get_proprietaire() == joueur)
            nb_terrain++;
    }
    // Si c'est une famille avec que 2 terrains et que le joueur les a tous, alors on veut renvoyer 3
    if ((numero < 4 || numero > 36) && nb_terrain == 2)
        nb_terrain = 3;

    return nb_terrain;
}


void Terrain::arreterSur(Joueur* joueur, bool fast_game){
    bool achat = false;

    // Si la Terrain est à personne
    if (proprietaire == NULL || proprietaire->est_en_vie() == false){
        cout << "Le Terrain n'appartient a personne. Vous avez " << joueur->get_solde() << " et le Terrain coute " << prix_achat <<"." << endl;
        cout << "Vous avez " << joueur_possession(joueur) << " terrain(s) de la meme couleur !" << endl;
        nb_maison = 0; // On remets le nb de maison à 0 (au cas ou une personne possedait le terrain avec des maisons et soit mort après)
        // On regarde si le joueur a assez d'argent
        if (joueur->get_solde() > prix_achat){
            cout << " Voulez-vous vous l'acheter? " << endl;
            string reponse = "init";

            while(reponse != "oui" && reponse != "OUI" && reponse != "Oui" && reponse != "non" && reponse != "Non" && reponse != "NON"){
                if (fast_game)
                    reponse = "Oui";
                else
                    cin >> reponse;

                if(reponse == "oui" || reponse == "OUI" || reponse == "Oui"){
                    cout << nom << " est a vous" << endl;
                    achat =  true;
                    proprietaire = joueur;
                    joueur->debiter(-prix_achat);

                }else if(reponse == "non" || reponse == "NON" || reponse == "Non"){
                    cout << "Tant pis" << endl;

                }else{
                    cout << "Veuillez repondre pas oui ou par non"<< endl;
                }
            }
        }
        else cout << "Vous n'avez pas assez d'argent pour l'acheter!" << endl;
    }

    // Si la Terrain est à un autre joueur
    if (proprietaire != NULL && proprietaire->est_en_vie() && proprietaire != joueur){
        int prix = loyer[nb_maison];

        if (color_mode){
            if (nb_maison == 0)
                cout << "Ce Terrain est a " << proprietaire->get_nom() << endl;
            if (nb_maison == 1)
                cout << "Ce Terrain est a " << proprietaire->get_nom() <<". Il possede " << nb_maison << " \033[32mmaison\033[0m." << endl;
            if (nb_maison > 1 && nb_maison < 5)
                cout << "Ce Terrain est a " << proprietaire->get_nom() <<". Il possede " << nb_maison << " \033[32mmaisons\033[0m." << endl;
            if (nb_maison == 5)
                cout << "Ce Terrain est a " << proprietaire->get_nom() <<". Il possede un \033[1;31mhotel\033[0m." << endl;
        }
        else{
            if (nb_maison == 0)
                cout << "Ce Terrain est a " << proprietaire->get_nom() << endl;
            if (nb_maison == 1)
                cout << "Ce Terrain est a " << proprietaire->get_nom() <<". Il possede " << nb_maison << " maison." << endl;
            if (nb_maison > 1 && nb_maison < 5)
                cout << "Ce Terrain est a " << proprietaire->get_nom() <<". Il possede " << nb_maison << " maisons." << endl;
            if (nb_maison == 5)
                cout << "Ce Terrain est a " << proprietaire->get_nom() <<". Il possede un hotel." << endl;
        }

        // Si le proprietaire n'a pas de maison mais tout les terrains de la famille
        if (nb_maison == 0 && joueur_possession(proprietaire) == 3){
                cout << "Le proprietaire possede tous les terrains du groupe, vous devez payer 2 fois plus cher !" << endl;
            prix = loyer[0] * 2;
        }

        cout << "Vous devez lui payer " << prix << endl;
        proprietaire->debiter(prix);
        joueur->debiter(-prix);
    }

    // Si la Terrain est au joueur actif
    if (proprietaire == joueur && joueur_possession(joueur) == 3){
        if (color_mode){
            if (nb_maison < 2)
                cout << "Ce Terrain est a vous et vous possedez tous les terrains du groupe. Il y a " << nb_maison << " \033[32mmaison\033[0m dessus." << endl;
            if (nb_maison >= 2 && nb_maison != 5)
                cout << "Ce Terrain est a vous. Il y a " << nb_maison << " \033[32mmaisons\033[0m dessus." << endl;
            if (nb_maison == 5)
                cout << "Ce Terrain est a vous. Il y a un \033[1;31mhotel\033[0m dessus." << endl;
        }
        else{
            if (nb_maison < 2)
                cout << "Ce Terrain est a vous et vous possedez tous les terrains du groupe. Il y a " << nb_maison << " maison dessus." << endl;
            if (nb_maison >= 2 && nb_maison != 5)
                cout << "Ce Terrain est a vous. Il y a " << nb_maison << " maisons dessus." << endl;
            if (nb_maison == 5)
                cout << "Ce Terrain est a vous. Il y a un hotel dessus." << endl;
        }

        int nb_max_maison = min(joueur->get_solde()/prix_maison, 5 - nb_maison);

        if (nb_max_maison != 0){
            if (color_mode){
                cout << "Combien de \033[32mmaison(s)\033[0m voulez-vous acheter ? Sachant que vous avez " << joueur->get_solde();
                cout << " et qu'une \033[32mmaison(s)\033[0m coute " << prix_maison << ". Si vous n'en voulez pas, repondez 0. " << endl;
            }
            else{
                cout << "Combien de maison(s) voulez-vous acheter ? Sachant que vous avez " << joueur->get_solde();
                cout << " et qu'une maison(s) coute " << prix_maison << ". Si vous n'en voulez pas, repondez 0. " << endl;
            }
            int reponse = -1;

            if (color_mode)
                cout << "Vous pouvez acheter au maximun " << nb_max_maison << " \033[32mmaison(s)\033[0m." << endl;
            else
                cout << "Vous pouvez acheter au maximun " << nb_max_maison << " maison(s)." << endl;
            while (reponse < 0 || reponse > nb_max_maison+1){
                if (fast_game)
                    reponse = nb_max_maison;
                else
                    cin >> reponse;

                if (reponse >0 && reponse <= nb_max_maison){
                    // Achate d'un hotel
                    if (nb_maison + reponse == 5){
                        if (color_mode)
                            cout << "Vous achetez un \033[1;31mhotel\033[0m." << endl;
                        else
                            cout << "Vous achetez un hotel." << endl;
                        joueur->set_nb_hotels(joueur->get_nb_hotels() + 1);
                        joueur->set_nb_maisons(joueur->get_nb_maisons() - nb_maison);
                    }
                    // Achat de maisons
                    else{
                        if (color_mode)
                            cout << "Vous achetez " << reponse << " \033[32mmaison(s)\033[0m." << endl;
                        else
                            cout << "Vous achetez " << reponse << " maison(s)." << endl;
                        joueur->set_nb_maisons(joueur->get_nb_maisons() + reponse);
                    }
                    joueur->debiter(-reponse * prix_maison);
                    cout << "Le loyer de ce terrain passe de " << loyer[nb_maison] << " a " << loyer[nb_maison+reponse] << endl;
                    nb_maison = nb_maison + reponse;
                }
                else cout << "Vous n'avez pas achete de maison" << endl;
            }
        }
    }

    // Si c'est chez lui mais il ne possède pas tous les terrains du groupe
    if (proprietaire == joueur && joueur_possession(joueur) != 3 && !achat){
        if (color_mode)
            cout << "Vous etes chez vous, cependant vous ne possedez pas tous les terrains du groupe. Vous ne pouvez donc pas acheter de \033[32mmaison\033[0m." << endl;
        else
            cout << "Vous etes chez vous, cependant vous ne possedez pas tous les terrains du groupe. Vous ne pouvez donc pas acheter de maison." << endl;
        cout << "Vous avez " << joueur_possession(joueur) << " terrain(s) du groupe" << endl;
    }
}
