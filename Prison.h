#ifndef PRISON_H
#define PRISON_H

#include <Case.h>


class Prison : public Case
{
    public:
        Prison();
        Prison(string nom, int numero);

        void arreterSur(Joueur*, bool);       // Si on tombe sur la case
};

#endif // PRISON_H
