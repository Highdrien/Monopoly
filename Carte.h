#ifndef CARTE_H
#define CARTE_H
#include <iostream>

using namespace std;

class Carte
{
    protected:
        int numero;     // num�ro de la carte
        int gain;       // argent recup�r� (ou perdu si gain est n�gatif)
        int aller_a;    // aller � la case num�ro 'aller_a'

        int action_special;
        /* action_special vaut: 1 si le joueur doit reculler de 3 cases
                                2 s'il pourra utilis� cette carte pour sortir de prison
                                3 s'il doit faire des petites r�parations (payer 25 par maisons et 100 par h�tels)
                                4 s'il doit faire des grosses r�parations (payer 40 par maisons et 115 par h�tels)
                                5 s'il on doit aller � la gare la plus proche
        */
        string texte;  // texte de la carte


    public:
        Carte();
        Carte(int numero, int reculer_3cases, int gain, int liberer_prison, int reparation_1, int reparation_2, int aller_a, string texte);
        // Getteur
        int get_numero(){return numero;};
        int get_gain(){return gain;};
        int get_aller_a(){return aller_a;};
        int get_action_special(){return action_special;};
        string get_texte(){return texte;};
};

#endif // CARTE_H
