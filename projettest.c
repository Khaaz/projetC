#include "projet.h"

void test (void)
{
    ListeLecteur listeL;
    Lecteur l;

    strcpy(l.numLecteur,"0001");
    strcpy(l.nom, "Bon");
    strcpy(l.prenom, "Jean");

    listeL = listeVide();
    listeL = insererLec(listeL, l);
}


int main(void)
{
    test();
    return 0;
}