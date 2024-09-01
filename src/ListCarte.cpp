#include "ListCarte.h"

ListCarte::ListCarte(){

    //Creation des cartes chances
    liste_carte_chance = new Carte[17];
    liste_carte_communaute = new Carte[17];

    liste_carte_chance[0]  = Carte( 1, 0,   50, 0, 0, 0, -1, "La Banque vous verse une dividende de 50e.");
    liste_carte_chance[1]  = Carte( 2, 0,  -20, 0, 0, 0, -1, "Amende pour ivresse : 20e.");
    liste_carte_chance[2]  = Carte( 3, 0,  -15, 0, 0, 0, -1, "Amende pour exces de vitesse : 15e.");
    liste_carte_chance[3]  = Carte( 4, 0,  100, 0, 0, 0, -1, "Vous avez gagne le prix de mots croises. Recevez 100e.");
    liste_carte_chance[4]  = Carte( 5, 0, -150, 0, 0, 0, -1, "Payez pour frais de scolarite 150e.");
    liste_carte_chance[5]  = Carte( 6, 0,  150, 0, 0, 0, -1, "Votre immeuble et votre pret rapportent. Vous devez toucher 150e.");
    liste_carte_chance[6]  = Carte( 7, 0,    0, 0, 0, 0, 24, "Rendez-vous a l'Avenue Henri-Martin.");
    liste_carte_chance[7]  = Carte( 8, 0,    0, 0, 0, 0, 30, "Allez en prison.");
    liste_carte_chance[8]  = Carte( 9, 0,    0, 0, 0, 0,  0, "Avancez jusqu'a la case Depart.");
    liste_carte_chance[9]  = Carte(10, 0,    0, 0, 0, 0, 39, "Rendez-vous a la rue de la Paix.");
    liste_carte_chance[10] = Carte(11, 0,    0, 0, 0, 0, 15, "Allez a la gare de Lyon.");
    liste_carte_chance[11] = Carte(12, 0,    0, 0, 0, 0, 11, "Avancez au Boulevard de la Vilette.");
    liste_carte_chance[12] = Carte(13, 0,    0, 0, 1, 0, -1, "Faites des reparations dans vos maisons. Versez pour chaque maison 25e et versez pour chaque hotel 100e.");
    liste_carte_chance[13] = Carte(14, 1,    0, 0, 0, 0, -1, "Reculez de trois cases.");
    liste_carte_chance[14] = Carte(15, 0,    0, 1, 0, 0, -1, "Vous etes libere de prison. Cette carte peut etre conservee jusqu'a ce qu'elle soit utilisee.");
    liste_carte_chance[15] = Carte(17, 0,    0, 0, 0, 0, -1, "Avancez jusqu'a la gare la plus proche");
    liste_carte_chance[16] = Carte(17, 0,    0, 0, 0, 0, -1, "Avancez jusqu'a la gare la plus proche");


    // Creation des cartes caisse de communaute

    liste_carte_communaute[0]  = Carte( 1, 0,  100, 0, 0, 0, -1, "Recevez votre revenu annuel 100e.");
    liste_carte_communaute[1]  = Carte( 2, 0,   50, 0, 0, 0, -1, "La vente de votre stock vous rapporte 50e.");
    liste_carte_communaute[2]  = Carte( 3, 0, -100, 0, 0, 0, -1, "Payez a l'Hopital 100e.");
    liste_carte_communaute[3]  = Carte( 4, 0,   25, 0, 0, 0, -1, "Recevez votre interet sur l'emprunt a 7%,  25e.");
    liste_carte_communaute[4]  = Carte( 5, 0,   20, 0, 0, 0, -1, "Les Contributions vous remboursent la somme de 20e.");
    liste_carte_communaute[5]  = Carte( 6, 0,  200, 0, 0, 0, -1, "Erreur de la Banque en votre faveur. Recevez 200e.");
    liste_carte_communaute[6]  = Carte( 7, 0,  -50, 0, 0, 0, -1, "Payez la note du Medecin 50e.");
    liste_carte_communaute[7]  = Carte( 8, 0,  80, 0, 0, 0, -1, "C'est votre anniversaire. Recevez 80e.");
    liste_carte_communaute[8]  = Carte( 9, 0,  100, 0, 0, 0, -1, "Vous heritez 100e.");
    liste_carte_communaute[9]  = Carte( 10, 0,  -50, 0, 0, 0, -1, "Payez votre police d'assurance s'elevant a 50e.");
    liste_carte_communaute[10]  = Carte(11, 0,   10, 0, 0, 0, -1, "Vous avez gagne le deuxieme Prix de Beaute. Recevez 10e.");
    liste_carte_communaute[11] = Carte(12, 0,    0, 0, 0, 0, 30, "Allez en prison.");
    liste_carte_communaute[12] = Carte(13, 0,    0, 0, 0, 0,  0, "Avancez jusqu'a la case Depart.");
    liste_carte_communaute[13] = Carte(14, 0,    0, 0, 0, 0,  1, "Retournez a Belleville.");
    liste_carte_communaute[14] = Carte(15, 0,    0, 1, 0, 0, -1, "Vous etes libere de prison. Cette carte peut etre conservee jusqu'a ce qu'elle soit utilisee.");
    liste_carte_communaute[15] = Carte(16, 0,    0, 0, 0, 1, -1, "Faites des reparations dans vos maisons. Versez pour chaque maison 40e et versez pour chaque hotel 115e.");
    liste_carte_communaute[16] = Carte(17, 0,    0, 0, 0, 0, -1, "Avancez jusqu'a la gare la plus proche");
}

Carte ListCarte::get_carte_chance(int i){
    return liste_carte_chance[i];
}

Carte ListCarte::get_carte_communautte(int i){
    return liste_carte_communaute[i];
}
