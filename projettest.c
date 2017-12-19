#include "projet.h"

void test (void)
{
    ListeLecteur listeL;
    Lecteur l1, l2;

    strcpy(l1.numLecteur,"0001");
    strcpy(l1.nom, "Bon");
    strcpy(l1.prenom, "Jean");

    strcpy(l2.numLecteur,"0010");
    strcpy(l2.nom, "Trescartes");
    strcpy(l2.prenom, "Alexis");

    listeL = listeVide();
    listeL = insererLec(listeL, l1);
    listeL = insererLec(listeL, l2);

    strcpy(l2.numLecteur,"0009");
    strcpy(l2.nom, "Trescartes");
    strcpy(l2.prenom, "Alexis");

    listeL = insererLec(listeL, l2);

    afficherLec(listeL);
}


int main(void)
{
    test();
    return 0;
}