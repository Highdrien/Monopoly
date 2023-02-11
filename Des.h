#ifndef DES_H
#define DES_H


class Des{
    private:
        int valeur_de1;    // valeur du d� 1
        int valeur_de2;    // valeur de d� 2
        bool meme_valeur;  // bool�en qui vaut true si les 2 d�s ont la m�me valeur (si on a fait un double)

    public:
        Des();
        int lancer();   // lance les 2 d�s et renvoie la somme des d�s
        // Getteur
        bool get_double(){return meme_valeur;};
        int get_des1(){return valeur_de1;};
        int get_des2(){return valeur_de2;};
        int get_valeur(){return valeur_de1 + valeur_de2;};
};

#endif // DES_H
