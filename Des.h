#ifndef DES_H
#define DES_H


class Des{
    private:
        int valeur_de1;    // valeur du dé 1
        int valeur_de2;    // valeur de dé 2
        bool meme_valeur;  // booléen qui vaut true si les 2 dés ont la même valeur (si on a fait un double)

    public:
        Des();
        int lancer();   // lance les 2 dés et renvoie la somme des dés
        // Getteur
        bool get_double(){return meme_valeur;};
        int get_des1(){return valeur_de1;};
        int get_des2(){return valeur_de2;};
        int get_valeur(){return valeur_de1 + valeur_de2;};
};

#endif // DES_H
