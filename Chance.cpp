#include "Chance.h"

#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using std::this_thread::sleep_for;
using namespace std::chrono_literals;

#include <iostream>
using namespace std;

Chance::Chance():Case(){
    cartes = ListCarte();
}

Chance::Chance(string nom, int numero):Case(nom, numero){
    cartes = ListCarte();
}


void Chance::arreterSur(Joueur* joueur, bool fast_game){
    cout << "Carte chance:" << endl;

    if (!fast_game)
        sleep_for(1000ms);
    srand((unsigned int)time(0));
    Carte carte = cartes.get_carte_chance(rand()%17);

    cout << carte.get_texte() << endl;
    // Si on paye qqch
    if (carte.get_gain() != 0)
        joueur->debiter(carte.get_gain());

    // Si on vas qqpart
    if (carte.get_aller_a() != -1){
        if (carte.get_aller_a() - joueur->get_position() < 0 && carte.get_aller_a() != 30){
            cout << "Vous passez par la case depart, vous gagnez 200" << endl;
            joueur->debiter(200);
        }
        joueur->set_position(carte.get_aller_a());
    }

    // Si on recule de 3 cases (action_special == 1)
    if (carte.get_action_special() == 1){
         if (joueur->get_position() <= 3 && joueur->get_position() != 0){
            cout << "Vous passez par la case depart, vous gagnez 200" << endl;
            joueur->debiter(200);
        }
        joueur->set_position((joueur->get_position()-3) %40);
    }

    // Si on gagne une carte de sortie de prison (action_special == 2)
    if (carte.get_action_special() == 2){
        joueur->set_carte_sortie_prison(true);
    }

    // Si on doit faire des reparation (action_special == 3 ou 4)
    if (carte.get_action_special() == 3){
        int prix = 25 * joueur->get_nb_maisons() + 100 * joueur->get_nb_hotels();
        cout << "Vous devez payer: " << prix << " pour les travaux dans vos maisons et hotels." << endl;
        joueur->debiter(-prix);
    }
    if (carte.get_action_special() == 4){
        int prix = 40 * joueur->get_nb_maisons() + 115 * joueur->get_nb_hotels();
        cout << "Vous devez payer: " << prix << " pour les travaux dans vos maisons et hotels." << endl;
        joueur->debiter(-prix);
    }

    // Si on doit aller à la gare la plus proche
    if (carte.get_action_special() == 5){
        int new_possition = joueur->get_position() +1;
        while (new_possition%5 != 0 || new_possition%2 != 1)
            new_possition++;
        if (new_possition >= 40){
            cout << "Vous passez par la case depart, vous gagnez 200" << endl;
            joueur->debiter(200);
        }
        joueur->set_position(new_possition%40);
    }
}

