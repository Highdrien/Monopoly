#include <iostream>

#include "Jeu.h"
#include "Plateau.h"
#include "Case.h"
#include "Des.h"

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <direct.h>

#include <iostream>
#include <string>
#include <fstream>

#include <ctime>

using namespace std;

int nb_files_in_parties(){
    // Compte le nombre d'éléments dans le dossier /partie
    struct _finddata_t D;
    int done=0;
    int hd;
    int compteur = 0;
    _chdir("parties");
    hd = _findfirst("*.*",&D);

    if (hd==-1)
        return 2;

    while (!done){
        compteur++;
        done = _findnext(hd,&D);
    }
    return compteur;
}

int get_nb_joueur_in_a_game(int numero_partie){
    string name = "partie" + to_string(numero_partie) + ".txt";
    ifstream fichier(name, ios::in);
    string ligne;

    try{
        if(fichier){
            getline(fichier, ligne);
            return stoi(ligne);
        }
        else
            throw -1;
    }
    catch (int){
        cout << "La partie numero " << numero_partie << " n'a pas ete trouve !" << endl;
        return 0;
    }
}

int main(){

    int nb_joueurs = 0;
    int numero_partie = nb_files_in_parties() - 1;
    string load_game = "non";
    string ans_color_mode = "non";
    bool color_mode = false;

    srand(time(NULL));

    cout << "\n\t\t Bienvenue dans le jeu Monopoly ! \n" << endl;

    // color mode
    cout << "Une version en couleur est disponible sur le CMD de Windows 11, voullez-vous l'activer ? (oui ou non) : ";
    cin >> ans_color_mode;
    if (ans_color_mode == "oui" || ans_color_mode == "OUI" || ans_color_mode == "Oui")
        color_mode = true;

    // load game
    cout << "Vous avez " << numero_partie -1 << " partie(s) sauvegardee(s)." << endl;
    if (numero_partie > 1){

        cout << "Voulez-vous reprendre une partie en cours (oui ou non) ? ";
        cin >> load_game;

        if (load_game == "oui" || load_game == "OUI" || load_game == "Oui"){
            int partie = 1;
            cout << "Quel est le numero de la partie que vous voulez reprendre ?" << endl;
            cin >> partie;
            Jeu j = Jeu(get_nb_joueur_in_a_game(partie), numero_partie, false, color_mode);
            j.loading_game(partie);
        }
        else
            load_game = "non";
    }
    if (numero_partie <= 1 || load_game == "non"){
        cout << "\n Lancement d'une nouvelle partie ! \n" << endl;

        //  choix du nombre de joueur
        cout << "Combien y aura-t-il de joueur ? ";
        cin >> nb_joueurs;

        // mode speed run (joue tout seul)
        if (nb_joueurs == 0){
            cout << "Le mode rapie a ete active !";
            Jeu j = Jeu(2, numero_partie, true, color_mode);
            j.game();
        }

        // mode normal
        else{
            while(nb_joueurs > 8 || nb_joueurs < 2){
                cout << "Impossible, le nombre maximum de joueur doit etre compris entre 2 et 8.\n";
                cout << "Combien y aura-t-il de joueur ? ";
                cin >> nb_joueurs;
            }
            cout << "Nous jouerons donc une partie avec " << nb_joueurs << " joueurs " <<endl;
            Jeu j = Jeu(nb_joueurs, numero_partie, false, color_mode);

            for(int i = 0; i < nb_joueurs; i++){
                cout << "Entrer le nom du joueur " << i+1 << ": ";
                string nom_joueur = "joueur "+to_string(i+1);
                cin >> nom_joueur;
                j.create_joueur(i, nom_joueur);
            }
            j.game();
        }
    }

    return 0;
}
