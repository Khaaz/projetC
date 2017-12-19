#include "projet.h"


// fonction Liste Lecteur

ListeLecteur listeVide (void)
{
    return NULL;
}

ListeLecteur insererEnTeteLec(ListeLecteur listeL, Lecteur lec)
{
    MaillonLecteur *m;
    m = (MaillonLecteur*)malloc(sizeof(MaillonLecteur));
    if (m == NULL) {
        printf("Problème malloc\n");
        exit(1);
    }

    m->l = lec;
    m->suivNum = listeL;

    return m;
}

ListeLecteur insererLecNum(ListeLecteur listeL, Lecteur lec, int *trouve)
{
    if (listeL == NULL)
        return insererEnTeteLec(listeL, lec, m);
    if ( strcmp(lec.numLecteur, listeL->l.numLecteur) < 0)
        return insererEnTeteLec(listeL, lec, m);
    if ( strcmp(lec.numLecteur, listeL->l.numLecteur) == 0) {
        printf("Lecteur déja présent\n");
        *trouve = 1;
        return listeL;
    }

    listeL->suivNum = insererLecNum(listeL->suivNum, lec, trouve);
    *trouve = 0;
    return listeL;
}


ListeLecteur insererLec(ListeLecteur listeL, Lecteur lec)
{
    MaillonLecteur *m;

    int trouve;
    listeL = insererLecNum(listeL, lec, &trouve);

    if (trouve == 0) {
        listeL = insererLecNom(listeL, lec, m, maux);
    }

    return listeL;
}

void afficherLec(ListeLecteur listeL)
{
    if(listeL == NULL) {
        printf("\n");
        return;
    }
    printf("%s\t%s\t%s\t%d %s %s %d\n",listeL->l.numLecteur,listeL->l.nom, listeL->l.prenom, listeL->l.adresse.numRue, listeL->l.adresse.nomRue, listeL->l.adresse.ville, listeL->l.adresse.numDepartement);
    afficherLec(listeL->suivNom);

}
