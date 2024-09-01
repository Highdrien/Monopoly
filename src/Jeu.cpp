#include "Jeu.h"
#include "Plateau.h"

#include <iostream>
#include <string>
#include <fstream>

#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using std::this_thread::sleep_for;

Jeu::Jeu(int nb_joueurs, int numero_partie, bool fast_game, bool color_mode){

    // Création du plateau
    plateau = Plateau();
    this->color_mode = color_mode;
    if (color_mode)
        plateau.color_mode();
    tour_de_jeu = 1;
    d = Des();

    // Créatation des joueurs
    joueur_actif = 0;
    this->nb_joueurs = nb_joueurs;
    list_joueurs = new Joueur[nb_joueurs];
    for (int i=0; i<nb_joueurs; i++)
        list_joueurs[i].set_nom("joueur "+to_string(i+1));

    // Activatin du jeu
    game_on = true;
    this->numero_partie = numero_partie;

    if (fast_game)
        this->fast_game = fast_game;
}

void Jeu::create_joueur(int i, string nom){
    list_joueurs[i].set_nom(nom);
    list_joueurs[i].set_numero_joueur(i+1);
}

void Jeu::affiche_joueurs(){
    for (int i=0; i<nb_joueurs; i++){
        if (list_joueurs[i].est_en_vie()){
            cout << "--- Joueur: " << list_joueurs[i].get_nom() << " ---" <<endl;
            cout << "solde: " << list_joueurs[i].get_solde() << endl;

            // On regarde si il est ne prison ou non
            if (list_joueurs[i].get_en_prison())
                cout << "position: \033[4mEn Prison\033[0m" << endl;
            else cout << "position: " << *plateau[list_joueurs[i].get_position()] << endl;

            // On regarde sont nombre de maisons/hotels
            //cout << "nombre de \033[32mmaison(s)\033[0m: " << list_joueurs[i].get_nb_maisons() << ", nombre d'\033[1;31mhotel(s)\033[0m: " << list_joueurs[i].get_nb_hotels() << endl;

            // cout << "Vous possedez:" << endl;
            // affiche_possession(&list_joueurs[i]);
        }
        else{
            cout << "--- Joueur: " << list_joueurs[i].get_nom() << " ---" <<endl;
            cout << "a perdu" << endl;
        }
    }
}


void Jeu::jouer(Joueur* joueur){

    int position_init = joueur->get_position();
    int position_final = position_init;

    // ----------------------------------------------
    // On regarde si le joueur est en prison ou non |
    // ----------------------------------------------
    if (joueur->get_en_prison() > 0 ){
        cout << "Vous etes en prison! \n Vous pouvez sortir dans " << joueur->get_en_prison() << " tour(s)"<< endl;
        cout << "Sauf si vous faites un double au lancer de des" << endl;
        d.lancer();
        cout << "Vous avez fait " << d.get_des1() << " et " << d.get_des2() << " au lancer de des" << endl;
        if (d.get_double()){
            cout << "Bravo, vous avez fait un double. Vous etes libre maintenant" << endl;
            joueur->set_prison(false);

            joueur->avance(d.get_valeur());
            position_final = joueur->get_position();
            cout << "Vous arrivez sur la case: " << *plateau[position_final] << endl;
            plateau[position_final]->arreterSur(joueur, fast_game);
            check_joueur(joueur);

            // On regarde s'il est arrivé sur la case chance
            if (position_final != joueur->get_position() && joueur->get_position() != 10){
                cout << "Vous arrivez sur la case: " << *plateau[joueur->get_position()] << endl;
                position_init = -1;
                position_final = joueur->get_position();
                plateau[position_final]->arreterSur(joueur, fast_game);
                check_joueur(joueur);
            }
        }
        else
            cout << "Malheureusement, vous n'avez pas fait de double. Vous restez en prison" << endl;
    }
    // -----------------------------------------------
    // On regarde si le joueur n'etait pas en prison |
    // -----------------------------------------------
    else{
        cout << "Vous avez fait " << d.lancer() << " au lancer de des" << endl;

        // On regarde si le joueur passe par la case départ
        if (position_init+d.get_valeur() >= 40){
            cout << "Vous passez par la case depart, vous recevez 200!" << endl;
            joueur->debiter(200);
        }

        joueur->avance(d.get_valeur());
        position_final = joueur->get_position();
        cout << "Vous arrivez sur la case: " << plateau[position_final]->get_nom() << endl;
        plateau[position_final]->arreterSur(joueur, fast_game);
        check_joueur(joueur);

        // On regarde si le joueur s'est déplacer qqpart avec une carte (autre qu'en prison)
        if (position_final != joueur->get_position() && joueur->get_position() != 10){
            cout << "Vous arrivez sur la case: " << *plateau[joueur->get_position()] << endl;
            position_init = -1;
            position_final = joueur->get_position();
            plateau[position_final]->arreterSur(joueur, fast_game);
            check_joueur(joueur);
        }

        // Dans le cas, où on tombe sur la case chance n°36 et qu'on recule de 3 cases (cases caise de communaute) et qu'on se redeplace
        if (position_init == -1 && position_final == 33 && joueur->get_position() != 33 && joueur->get_position() != 10){
            cout << "Vous arrivez sur la case: " << *plateau[joueur->get_position()] << endl;
            plateau[joueur->get_position()]->arreterSur(joueur, fast_game);
            check_joueur(joueur);
        }
    }
    joueur->reduit_peine_prison();
    joueur_actif = (joueur_actif + 1) % nb_joueurs;
}

void Jeu::tour(){
    cout << "\n=============================================================="<< endl;
    cout << "             TOUR NUMERO: " << tour_de_jeu << "              " <<endl;
    cout << "==============================================================" << endl;

    for (int i=0; i<nb_joueurs; i++){

        // On regarde si le joueur est en vie
        if (list_joueurs[i].est_en_vie() && game_on){

            int rejoue = 1;     // nombre de fois que je joueur rejoue (au bout de 3 il va en prison)

            cout << "\n############### Tour de : " << list_joueurs[i].get_nom() << " ###############" << endl;

            jouer(&list_joueurs[i]);
            if (!fast_game)
                sleep_for(2s);

            // On regarde si le joueur a fait un double
            while (d.get_double() && rejoue != -1 && list_joueurs[i].est_en_vie()){

                // Si il vient de faire 3 double d'affilée, il va en prison
                if (rejoue == 3){
                    cout << "Vous venez de faire 3 doubles d'affilee, vous allez en prison" << endl;
                    list_joueurs[i].set_prison(true);
                    rejoue = -1;
                }
                // Sinon il rejoue simplement
                else{
                    cout << "-----Vous avez fait un double, vous pouvez rejouer.-----" << endl;
                jouer(&list_joueurs[i]);
                rejoue++;
                }
                if (!fast_game)
                    sleep_for(2s);
            }
        }

        // On regarde si c'est une fin de partie (cad qu'il reste qu'un seul joueur en vie)
        if (compte_joueur_en_vie() == 1 && game_on){
            for (int i=0; i<nb_joueurs; i++){
                if (list_joueurs[i].est_en_vie()){
                    cout << "\n================================================="<< endl;
                    cout << "   Bravo a " << list_joueurs[i].get_nom() << " qui a gagne la partie !!              " <<endl;
                    cout << "=================================================" << endl;
                    game_on = false;
                }
            }
        }

    }
    tour_de_jeu++;
    cout << "\nStatuts des joueurs" << endl;
    affiche_joueurs();
    if (!fast_game)
        sleep_for(2s);
}

void Jeu::game(){
    int tour_max = 1000;
    int reponse = 1;

    cout << "Lancement de la partie numero: " << numero_partie << endl;
    while (tour_de_jeu < tour_max && game_on){
        tour();
        if (game_on){
            cout << "\n---Fin du tour---" << endl;

            // Affiche les possession des joueurs en vie
            for (int i=0; i<nb_joueurs; i++){
                cout << "\n";
                if (list_joueurs[i].est_en_vie())
                    affiche_possession(&list_joueurs[i]);
            }

            // si ce n'est pas une partie rapide
            if (!fast_game){
                cout << "\nQue vous voulez-vous faire ?" << endl;
                cout << "1:continuer - 2:faire des echanges - 3:sauvegarder - 4:quitter - 5:sauvegarder et quitter" << endl;
                cin >> reponse;

                // trade
                while (reponse == 2){
                    trade();

                    // Affiche les possession des joueurs en vie
                    for (int i=0; i<nb_joueurs; i++){
                        cout << "\n";
                        if (list_joueurs[i].est_en_vie())
                            affiche_possession(&list_joueurs[i]);
                    }

                    cout << "\nQue vous voulez-vous faire ?" << endl;
                    cout << "1:continuer - 2:refaire des echanges - 3:sauvegarder - 4:quitter - 5:sauvegarder et quitter" << endl;
                    cin >> reponse;
                }

                //Sauvegarde de la partie
                if (reponse == 3){
                    saving_game();
                    cout << "la partie numero " << numero_partie << " vient d'etre sauvegardee !" << endl;
                }

                // Arret du jeu
                if (reponse == 4){
                    cout << "\n-----Fin du jeu-----" << endl;
                    game_on = false;
                }

                if (reponse == 5){
                    saving_game();
                    cout << "\n-----Fin du jeu-----" << endl;
                    cout << "la partie numero " << numero_partie << " vient d'etre sauvegardee !" << endl;
                    game_on = false;
                }
            }
        }
    }
    cout << "\n\nMerci d'avoir joue au monopoly :)" << endl;
}


int Jeu::compte_joueur_en_vie(){
    int compte = 0;
    for (int i=0; i<nb_joueurs; i++){
        if (list_joueurs[i].est_en_vie()){
            compte++;
        }
    }
    return compte;
}

void Jeu::affiche_possession(Joueur* joueur){
    cout << "Le joueur " << joueur->get_nom() << " possede:" << endl;
    for (int i=0; i<40; i++){
        if (plateau[i]->get_proprietaire() == joueur)
            if (plateau[i]->get_nb_maison() == 0)
                cout << plateau[i]->get_nom() << endl;
            else if (plateau[i]->get_nb_maison() !=5)
                    if (color_mode)
                        cout << plateau[i]->get_nom() << " avec " << plateau[i]->get_nb_maison() << " \033[32mmaison(s)\033[0m" << endl;
                    else
                        cout << plateau[i]->get_nom() << " avec " << plateau[i]->get_nb_maison() << " maison(s)" << endl;
                else
                    if (color_mode)
                        cout << plateau[i]->get_nom() << " avec un \033[1;31mhotel\033[0m" << endl;
                    else
                        cout << plateau[i]->get_nom() << " avec un hotel" << endl;
    }
}

void Jeu::check_joueur(Joueur* joueur){
    if (joueur->get_solde() < 0){
        int prix_de_revente;
        cout << " !!! Votre solde est negatif !!! Les huissiers frappent a votre porte" << endl;

        // On lui enlève en priorité ses maisons/hotels
        for (int i=0; i<40; i++){
            if (plateau[i]->get_proprietaire() == joueur && plateau[i]->get_nb_maison() != 0 && joueur->get_solde() < 0){
                prix_de_revente = plateau[i]->get_nb_maison() * plateau[i]->get_prix_maison();

                // si c'est des maisons
                if (plateau[i]->get_nb_maison() != 5)
                    if (color_mode)
                        cout << "Les huissiers saisissent " << plateau[i]->get_nb_maison() << " \033[32mmaison(s)\033[0m a " << plateau[i]->get_nom() << " pour " << prix_de_revente << endl;
                    else
                        cout << "Les huissiers saisissent " << plateau[i]->get_nb_maison() << " maison(s) a " << plateau[i]->get_nom() << " pour " << prix_de_revente << endl;
                // si c'est un hotel
                else
                    if (color_mode)
                        cout << "Les huissiers saisissent votre \033[1;31mhotel\033[0m a " << plateau[i]->get_nom() << " pour " << prix_de_revente << endl;
                    else
                        cout << "Les huissiers saisissent votre hotel a " << plateau[i]->get_nom() << " pour " << prix_de_revente << endl;

                joueur->debiter(prix_de_revente);
                joueur->set_nb_maisons(joueur->get_nb_maisons() - plateau[i]->get_nb_maison());
                plateau[i]->set_nb_maison(0);
            }
        }

        // On lui enlève ensuite ses proriété
        for (int i=0; i<40; i++){
            if (plateau[i]->get_proprietaire() == joueur && joueur->get_solde() < 0){
                prix_de_revente = plateau[i]->get_prix_achat();
                cout << "Les huissiers saisissent " << plateau[i]->get_nom() << endl;
                joueur->debiter(prix_de_revente);
                plateau[i]->set_proprietaire(NULL);
            }
        }
    }

    // Si malgrès la revente de toutes ses propriétés, il a toujours pas d'argent, le joueur pert
    if (joueur->get_solde() < 0){
        joueur->set_en_vie(false);
        cout << "---------------------" << endl;
        cout << "  " << joueur->get_nom() << " A PERDU  " << endl;
        cout << "---------------------" << endl;
    }

}
int Jeu::numero_joueur(string nom_joueur){
    int rep = -1;
    for (int i=0; i<nb_joueurs; i++){
        if (list_joueurs[i].get_nom() == nom_joueur && list_joueurs[i].est_en_vie())
            rep = i;
    }
    return rep;
}

void Jeu::trade(){
    string nom_joueur_1 = "";
    string nom_joueur_2 = "";

    Joueur* joueur_1 = &list_joueurs[0];
    Joueur* joueur_2 = &list_joueurs[1];

    // S'il y a plus de 2 joueurs dans la partie
    if (nb_joueurs > 2){


        cout << "\nQuels sont les 2 joueurs qui veullent echanger des proprietes ?" << endl;
        cout << "Nom du joueur numero 1: ";
        cin >> nom_joueur_1;
        cout << "Nom du joueur numero 2: ";
        cin >> nom_joueur_2;

        while (numero_joueur(nom_joueur_1) == -1){
            cout << "Le joueur " << nom_joueur_1 << " n'existe pas ou n'est plus actif, veillez le resesir" << endl;
            cout << "Nom du joueur numero 1: ";
            cin >> nom_joueur_1;
        }

        while (numero_joueur(nom_joueur_2) == -1){
            cout << "Le joueur " << nom_joueur_2 << " n'existe pas ou n'est plus actif, veillez le resesir" << endl;
            cout << "Nom du joueur numero 2: ";
            cin >> nom_joueur_2;
        }

        joueur_1 = &list_joueurs[numero_joueur(nom_joueur_1)];
        joueur_2 = &list_joueurs[numero_joueur(nom_joueur_2)];
    }

    // S'il n'y a que 2 joueurs dans la partie
    else{
        nom_joueur_1 = joueur_1->get_nom();
        nom_joueur_2 = joueur_2->get_nom();
    }

    // Si c'est pas les mêmes joueur
    if (joueur_1 != joueur_2){
        int i1 = 0;
        int i2 = 0;

        // affichage des possessions des 2 joueurs
        cout << "\n" << nom_joueur_1 <<" possede :" << endl;
        for (int i=0; i<40; i++){
            if (plateau[i]->get_proprietaire() == joueur_1){
                i1++;
                cout << i1 << " : " << plateau[i]->get_nom() << "   prix: " << plateau[i]->get_prix_achat() << endl;
            }
        }

        cout << "\n" << nom_joueur_2 <<" possede :" << endl;
        for (int i=0; i<40; i++){
            if (plateau[i]->get_proprietaire() == joueur_2){
                i2++;
                cout << i2 << " : " << plateau[i]->get_nom() << "   prix: " << plateau[i]->get_prix_achat() << endl;
            }
        }

        int t1 = -1;
        int t2 = -1;

        // récupération de l'indice des propriétées
        cout << "\nEchange en cours, ecrivez le numero de la propriete que vous voulez echnager, mettez -1 si vous ne voullez rien echanger" << endl;
        cout << "Numero de la propriete que veut echanger " << nom_joueur_1 << " : ";
        cin >> t1;
        cout << "Numero de la propriete que veut echanger " << nom_joueur_2 << " : ";
        cin >> t2;

        while (t1 > i1 || t1 < -1){
            cout << "entrer un nombre entre -1 et " << i1 << endl;
            cin >> t1;
        }

        while (t2 > i2 || t2 < -1){
            cout << "entrer un nombre entre -1 et " << i2 << endl;
            cin >> t2;
        }

        i1 = 0;
        i2 = 0;

        for (int i=0; i<40; i++){
            if (plateau[i]->get_proprietaire() == joueur_1)
                i1++;
            if (plateau[i]->get_proprietaire() == joueur_2)
                i2++;
            if (i1 == t1)
                t1 = i;
            if (i2 == t2)
                t2 = i;
        }

        // Échange des propriétés
        int prix = 0;

        // le joueur 2 vent sa propriété au joueur 1
        if (t1 == -1 && t2 != -1){
            prix = plateau[t2]->get_prix_achat();
            cout << nom_joueur_1 << " doit " << prix << " a " << nom_joueur_2 << endl;

            if (joueur_1->get_solde() > prix){
                joueur_2->debiter(prix);
                joueur_1->debiter(-prix);
                plateau[t2]->set_proprietaire(joueur_1);

                cout << nom_joueur_1 << " posede maintenant " <<  plateau[t2]->get_nom() << endl;
            }

            else
                cout << nom_joueur_1 << " n'a pas assez pour payer l'echange" << endl;
        }

        // le joueur 1 vent sa propriété au joueur 2
        if (t1 != -1 && t2 == -1){
            prix = plateau[t1]->get_prix_achat();
            cout << nom_joueur_2 << " doit " << prix << " a " << nom_joueur_1 << endl;

            if (joueur_1->get_solde() > prix){
                joueur_1->debiter(prix);
                joueur_2->debiter(-prix);
                plateau[t1]->set_proprietaire(joueur_2);

                cout << nom_joueur_2 << " posede maintenant " <<  plateau[t1]->get_nom() << endl;
            }

            else
                cout << nom_joueur_2 << " n'a pas assez pour payer l'echange" << endl;
        }

        // échange de propriété
        if (t1 != -1 && t2 != -1){
            prix = plateau[t1]->get_prix_achat() - plateau[t2]->get_prix_achat();

            // Si le joueur 2 doit payer le joueur 1
            if (prix > 0){
                cout << nom_joueur_2 << " doit " << prix << " a " << nom_joueur_1 << endl;

                // si le joueur 2 a assez d'argent pour l'échange
                if (joueur_2->get_solde() > prix){
                    joueur_1->debiter(prix);
                    joueur_2->debiter(-prix);

                    plateau[t1]->set_proprietaire(joueur_2);
                    plateau[t2]->set_proprietaire(joueur_1);

                    cout << nom_joueur_1 << " posede maintenant " <<  plateau[t2]->get_nom() << endl;
                    cout << nom_joueur_2 << " posede maintenant " <<  plateau[t1]->get_nom() << endl;
                }

                else
                    cout << nom_joueur_2 << " n'a pas assez pour payer l'echange" << endl;
            }

            // Si le joueur 1 doit payer le joueur 2
            if (prix < 0){
                cout << nom_joueur_1 << " doit " << -prix << " a " << nom_joueur_2 << endl;

                // si le joueur 1 a assez d'argent pour l'échange
                if (joueur_1->get_solde() > -prix){
                    joueur_2->debiter(prix);
                    joueur_1->debiter(-prix);

                    plateau[t1]->set_proprietaire(joueur_2);
                    plateau[t2]->set_proprietaire(joueur_1);

                    cout << nom_joueur_1 << " posede maintenant " <<  plateau[t2]->get_nom() << endl;
                    cout << nom_joueur_2 << " posede maintenant " <<  plateau[t1]->get_nom() << endl;
                }

                else
                    cout << nom_joueur_1 << " n'a pas assez pour payer l'echange" << endl;
            }

            // Si c'est le meme prix
            if (prix == 0){
                plateau[t1]->set_proprietaire(joueur_2);
                plateau[t2]->set_proprietaire(joueur_1);

                cout << nom_joueur_1 << " posede maintenant " <<  plateau[t2]->get_nom() << endl;
                cout << nom_joueur_2 << " posede maintenant " <<  plateau[t1]->get_nom() << endl;
            }
        }
    }

    else
        cout << "Erreur, veillez saisir 2 joueurs differents" << endl;
}

// --------------------------
// Sauvegarde de la  partie |
// --------------------------
void Jeu::saving_game(){
    string name = "partie" + to_string(numero_partie) + ".txt";
    ofstream fichier(name, ios::out | ios::trunc);

    // sauvegarde des joueurs
    fichier << nb_joueurs << endl;
    fichier << tour_de_jeu << endl;
    Joueur* j = &list_joueurs[0];
    for (int i=0; i<nb_joueurs; i++){
        j = &list_joueurs[i];
        fichier << j->get_nom() << endl;
        fichier << j->get_solde() << endl;
        fichier << j->get_position() << endl;
        fichier << j->est_en_vie() << endl;
        fichier << j->get_en_prison() << endl;
        fichier << j->get_carte_sortie_prison() << endl;
        fichier << j->get_nb_gares() << endl;
        fichier << j->get_nb_compagnies() << endl;
        fichier << j->get_nb_maisons() << endl;
        fichier << j->get_nb_hotels() << endl;
    }

    cout << "sauvegarde des possessions" << endl;
    // sauvegarde des possessions
    for (int i=0; i<40; i++){

        if (plateau[i]->get_proprietaire() != NULL)
            fichier << plateau[i]->get_proprietaire()->get_numero_joueur() << endl;

        else
            fichier << 0 << endl;

        fichier << plateau[i]->get_nb_maison() << endl;
    }
}

// -------------------------
// Chargement d'une partie |
// -------------------------
void Jeu::loading_game(int numero_partie){
    this->numero_partie = numero_partie;

    string name = "partie" + to_string(numero_partie) + ".txt";
    ifstream fichier(name, ios::in);

    string ligne;

    if(fichier){
        // nombre de joueur
        getline(fichier, ligne);
        int nb_joueur = stoi(ligne);
        cout << "nb joueur: " << nb_joueur << endl;

        // tour de jeu
        getline(fichier, ligne);
        tour_de_jeu = stoi(ligne);

        for (int i=0; i<nb_joueurs; i++)
            list_joueurs[i].set_nom("joueur "+to_string(i+1));

        // chargement des donneés des joueurs
        for (int i=0; i<nb_joueur; i++){
            // nom
            getline(fichier, ligne);
            list_joueurs[i].set_nom(ligne);

            // solde
            getline(fichier, ligne);
            list_joueurs[i].set_solde(stoi(ligne));

            // position
            getline(fichier, ligne);
            list_joueurs[i].set_position(stoi(ligne));

            // en vie
            getline(fichier, ligne);
            list_joueurs[i].set_en_vie(stoi(ligne));

            // en prison
            getline(fichier, ligne);
            list_joueurs[i].set_en_prison(stoi(ligne));

            // carte prison
            getline(fichier, ligne);
            list_joueurs[i].set_carte_sortie_prison(stoi(ligne));

            // nb gares
            getline(fichier, ligne);
            list_joueurs[i].set_nb_gares(stoi(ligne));

            // nb compagnie
            getline(fichier, ligne);
            list_joueurs[i].set_nb_compagnies(stoi(ligne));

            // nb maisons
            getline(fichier, ligne);
            list_joueurs[i].set_nb_maisons(stoi(ligne));

            // nb hotels
            getline(fichier, ligne);
            list_joueurs[i].set_nb_hotels(stoi(ligne));

            // numero du joueur
            list_joueurs[i].set_numero_joueur(i+1);
        }

        // chargement des terrains
        for (int i=0; i<40; i++){

            // possession d'une propriété
            getline(fichier, ligne);
            if (ligne != "0"){
                plateau[i]->set_proprietaire(&list_joueurs[stoi(ligne)-1]);

                // On regarde les maisons
                getline(fichier, ligne);
                if (ligne != "0")
                    plateau[i]->set_nb_maison(stoi(ligne));
            }
            else
                getline(fichier, ligne);
        }

        cout << "\nStatuts des joueurs" << endl;
        affiche_joueurs();
        sleep_for(2s);

        cout << "\nPossessions des joueurs:" << endl;
        for (int i=0; i<nb_joueurs; i++){
            cout << "\n";
            if (list_joueurs[i].est_en_vie())
                affiche_possession(&list_joueurs[i]);
        }
        cout << "\n";
        sleep_for(2s);

        game();

    }
    else
        cerr << "Impossible d'ouvrir le fichier : " << name << endl;
}
