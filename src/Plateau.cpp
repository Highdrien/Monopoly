#include "Plateau.h"
#include "Terrain.h"
#include "Gare.h"
#include "Compagnie.h"
#include "Taxes.h"
#include "Prison.h"
#include "Communaute.h"
#include "Chance.h"
#include "Depart.h"
#include "Parc.h"

#include <iostream>
using namespace std;

Plateau::Plateau()
{
    Terrain* lesTerrains = new Terrain[22];
    Gare* lesGares = new Gare[4];
    Compagnie* lesCompagnies = new Compagnie[2];
    Communaute* lesCommunautes = new Communaute[3];
    Chance* lesChances = new Chance[3];
    Taxes* lesTaxes = new Taxes[2];
    Prison* lesPrisons = new Prison[2];
    Depart* leDepart = new Depart("Depart");
    Parc* leParc = new Parc("Parc");

    // Création des Terrains
    lesTerrains[0]  = Terrain("Boulevard de Belleville", 60, 1, 2, 10, 30, 90, 160, 250, 50);
    lesTerrains[1]  = Terrain("Rue Lecourbe", 60, 3, 4, 20, 60, 180, 320, 450, 50);
    lesTerrains[2]  = Terrain("Rue de Vaugirard", 100, 6, 6, 30, 90, 270, 400, 550, 50);
    lesTerrains[3]  = Terrain("Rue de Courcelles", 100, 8, 6, 30, 90, 270, 400, 550, 50);
    lesTerrains[4]  = Terrain("Avenue de la Republique", 120, 9, 8, 40, 100, 300, 450, 600, 50);
    lesTerrains[5]  = Terrain("Boulevard de la Villette", 140, 11, 10, 50, 150, 450, 625, 750, 100);
    lesTerrains[6]  = Terrain("Avenue de Neuilly", 140, 13, 10, 50, 150, 450, 625, 750, 100);
    lesTerrains[7]  = Terrain("Rue de Paradis", 160, 14, 12, 60, 180, 500, 700, 900, 100);
    lesTerrains[8]  = Terrain("Avenue Mozard", 180, 16, 14, 70, 200, 550, 750, 950, 100);
    lesTerrains[9]  = Terrain("Boulevard Saint Michel", 180, 18, 14, 70, 200, 550, 750, 950, 100);
    lesTerrains[10] = Terrain("Place Pigalle", 200, 19, 16, 80, 220, 600, 800, 1000, 100);
    lesTerrains[11] = Terrain("Avenue Matignon", 220, 21, 18, 90, 250, 700, 875, 1050, 150);
    lesTerrains[12] = Terrain("Boulevard Malesherbes", 220, 23, 18, 90, 250, 700, 875, 1050, 150);
    lesTerrains[13] = Terrain("Avenue Henri-Martin", 240, 24, 20, 100, 300, 750, 925, 1100, 150);
    lesTerrains[14] = Terrain("Faubourg Saint-Honore", 260, 26, 22, 110, 330, 800, 975, 1150, 150);
    lesTerrains[15] = Terrain("Place de la Bourse", 260,  27, 22, 110, 330, 800, 975, 1150, 150);
    lesTerrains[16] = Terrain("Rue de la Fayette", 280, 29, 24, 120, 360, 850, 1025, 1200, 150);
    lesTerrains[17] = Terrain("Avenue de Breteuil", 300, 31, 26, 130, 390, 900, 1100, 1275, 200);
    lesTerrains[18] = Terrain("Avenue Foch", 300, 32,  26, 130, 390, 900, 1100, 1275, 200);
    lesTerrains[19] = Terrain("Boulevard des Capucines",  320,  34,  28, 150, 450, 1000, 1200, 1400, 200);
    lesTerrains[20] = Terrain("Avenue des Champs-Elysees", 350,  37, 35, 175, 500, 1100, 1300, 1500, 200);
    lesTerrains[21] = Terrain("Rue de la Paix", 400, 39,  50, 200, 600, 1400, 1700, 2000, 200);

    // Création des Gares
    lesGares[0] = Gare("Gare Montparnasse", 5, 25, 200);
    lesGares[1] = Gare("Gare de Lyon", 15, 25, 200);
    lesGares[2] = Gare("Gare du Nord", 25, 25, 200);
    lesGares[3] = Gare("Gare Saint Lazare", 35, 25, 200);

    // Création des Compagnie
    lesCompagnies[0] = Compagnie("Compagnie de distribution d'electricite", 12, 12, 150);
    lesCompagnies[1] = Compagnie("Compagnie de distribution des eaux", 28, 12, 150);

    // Créations des cases communaute
    lesCommunautes[0] = Communaute("Caise de Communaute", 2);
    lesCommunautes[1] = Communaute("Caise de Communaute", 17);
    lesCommunautes[2] = Communaute("Caise de Communaute", 33);

    // Création des cases chance
    lesChances[0] = Chance("Chance", 7);
    lesChances[1] = Chance("Chance", 22);
    lesChances[2] = Chance("Chance", 36);

    // Création des cases taxes
    lesTaxes[0] = Taxes("Impots sur le revenu", 38, 200);
    lesTaxes[1] = Taxes("Taxe de Luxe", 4, 100);

    // Création des cases "autre"
    lesPrisons[0] = Prison("Simple Visite", 10);
    lesPrisons[1] = Prison("Allez en Prison", 30);


    // Stockage éléments dans liste
    liste_cases = new Case*[40];
    liste_cases[0]  = leDepart;
    liste_cases[1]  = &lesTerrains[0];
    liste_cases[2]  = &lesCommunautes[0];
    liste_cases[3]  = &lesTerrains[1];
    liste_cases[4]  = &lesTaxes[0];
    liste_cases[5]  = &lesGares[0];
    liste_cases[6]  = &lesTerrains[2];
    liste_cases[7]  = &lesChances[0];
    liste_cases[8]  = &lesTerrains[3];
    liste_cases[9]  = &lesTerrains[4];
    liste_cases[10] = &lesPrisons[0];
    liste_cases[11] = &lesTerrains[5];
    liste_cases[12] = &lesCompagnies[0];
    liste_cases[13] = &lesTerrains[6];
    liste_cases[14] = &lesTerrains[7];
    liste_cases[15] = &lesGares[1];
    liste_cases[16] = &lesTerrains[8];
    liste_cases[17] = &lesCommunautes[1];
    liste_cases[18] = &lesTerrains[9];
    liste_cases[19] = &lesTerrains[10];
    liste_cases[20] = leParc;
    liste_cases[21] = &lesTerrains[11];
    liste_cases[22] = &lesChances[1];
    liste_cases[23] = &lesTerrains[12];
    liste_cases[24] = &lesTerrains[13];
    liste_cases[25] = &lesGares[2];
    liste_cases[26] = &lesTerrains[14];
    liste_cases[27] = &lesTerrains[15];
    liste_cases[28] = &lesCompagnies[1];
    liste_cases[29] = &lesTerrains[16];
    liste_cases[30] = &lesPrisons[1];
    liste_cases[31] = &lesTerrains[17];
    liste_cases[32] = &lesTerrains[18];
    liste_cases[33] = &lesCommunautes[2];
    liste_cases[34] = &lesTerrains[19];
    liste_cases[35] = &lesGares[3];
    liste_cases[36] = &lesChances[2];
    liste_cases[37] = &lesTerrains[20];
    liste_cases[38] = &lesTaxes[1];
    liste_cases[39] = &lesTerrains[21];

    // relation de groupe Terrain
    lesTerrains[0].setGroupe(&lesTerrains[0], &lesTerrains[1], NULL);
    lesTerrains[1].setGroupe(&lesTerrains[0], &lesTerrains[1], NULL);

    for (int i=0; i<6; i++){
        lesTerrains[3*i+2].setGroupe(&lesTerrains[3*i+2], &lesTerrains[3*i+3], &lesTerrains[3*i+4]);
        lesTerrains[3*i+3].setGroupe(&lesTerrains[3*i+2], &lesTerrains[3*i+3], &lesTerrains[3*i+4]);
        lesTerrains[3*i+4].setGroupe(&lesTerrains[3*i+2], &lesTerrains[3*i+3], &lesTerrains[3*i+4]);
    }

    lesTerrains[20].setGroupe(&lesTerrains[20], &lesTerrains[21], NULL);
    lesTerrains[21].setGroupe(&lesTerrains[20], &lesTerrains[21], NULL);
}


void Plateau::color_mode(){
    liste_cases[0]->set_nom("\033[4mDepart\033[0m");
    liste_cases[1]->set_nom("\033[1;30mBoulevard de Belleville\033[0m");
    liste_cases[2]->set_nom("\033[4mCaise de Communaute\033[0m");
    liste_cases[3]->set_nom("\033[1;30mRue Lecourbe\033[0m");
    liste_cases[4]->set_nom("\033[4mImpots sur le revenu\033[0m");
    liste_cases[5]->set_nom("\033[1;30mGare Montparnasse\033[0m");
    liste_cases[6]->set_nom("\033[1;36mRue de Vaugirard\033[0m");
    liste_cases[7]->set_nom("\033[4mChance\033[0m");
    liste_cases[8]->set_nom("\033[1;36mRue de Courcelles\033[0m");
    liste_cases[9]->set_nom("\033[1;36mAvenue de la Republique\033[0m");
    liste_cases[10]->set_nom("\033[4mSimple Visite\033[0m");
    liste_cases[11]->set_nom("\033[1;35mBoulevard de la Villette\033[0m");
    liste_cases[12]->set_nom("\033[4mCompagnie de distribution d'electricite\033[0m");
    liste_cases[13]->set_nom("\033[1;35mAvenue de Neuilly\033[0m");
    liste_cases[14]->set_nom("\033[1;35mRue de Paradis\033[0m");
    liste_cases[15]->set_nom("\033[1;30mGare de Lyon\033[0m");
    liste_cases[16]->set_nom("\033[33mAvenue Mozard\033[0m");
    liste_cases[17]->set_nom("\033[4mCaise de Communaute\033[0m");
    liste_cases[18]->set_nom("\033[33mBoulevard Saint Michel\033[0m");
    liste_cases[19]->set_nom("\033[33mPlace Pigalle\033[0m");
    liste_cases[20]->set_nom("\033[4mParc\033[0m");
    liste_cases[21]->set_nom("\033[31mAvenue Matignon\033[0m");
    liste_cases[22]->set_nom("\033[4mChance\033[0m");
    liste_cases[23]->set_nom("\033[31mBoulevard Malesherbes\033[0m");
    liste_cases[24]->set_nom("\033[31mAvenue Henri-Martin\033[0m");
    liste_cases[25]->set_nom("\033[1;30mGare du Nord\033[0m");
    liste_cases[26]->set_nom("\033[1;33mFaubourg Saint-Honore\033[0m");
    liste_cases[27]->set_nom("\033[1;33mPlace de la Bourse\033[0m");
    liste_cases[28]->set_nom("\033[4mCompagnie de distribution des eaux\033[0m");
    liste_cases[29]->set_nom("\033[1;33mRue de la Fayette\033[0m");
    liste_cases[30]->set_nom("\033[4mAllez en Prison\033[0m");
    liste_cases[31]->set_nom("\033[1;32mAvenue de Breteuil\033[0m");
    liste_cases[32]->set_nom("\033[1;32mAvenue Foch\033[0m");
    liste_cases[33]->set_nom("\033[4mCaise de Communaute\033[0m");
    liste_cases[34]->set_nom("\033[1;32mBoulevard des Capucines\033[0m");
    liste_cases[35]->set_nom("\033[1;30mGare Saint Lazare\033[0m");
    liste_cases[36]->set_nom("\033[4mChance\033[0m");
    liste_cases[37]->set_nom("\033[1;34mAvenue des Champs-Elysees\033[0m");
    liste_cases[38]->set_nom("\033[4mTaxe de Luxe\033[0m");
    liste_cases[39]->set_nom("\033[1;34mRue de la Paix\033[0m");
}


Case* Plateau::operator[](int i){
    return get_cases(i);
}
