#ifndef TAXES_H
#define TAXES_H

#include <Case.h>

class Taxes : public Case
{
    private:
        int taxes_a_payer;      // prix à payer

    public:
        Taxes();
        Taxes(string nom, int numero, int taxes_a_payer);

        void arreterSur(Joueur*, bool);   // Si on tombe sur la case
};

#endif // TAXES_H
