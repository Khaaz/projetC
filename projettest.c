#include "projet.h"

void test (void)
{
    ListeLecteur listeL;
    Lecteur l;

    l.numLecteur = "0001";
    l.nom = "Bon";
    l.prenom = "Jean";

    listeL = listeVide();
    listeL = insererLec(listeL, l);
}


int main(void)
{
    test();
    return 0;
}