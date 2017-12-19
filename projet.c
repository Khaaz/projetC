#include "projet.h"


// fonction Liste Lecteur

ListeLecteur listeVide (void)
{
    return NULL;
}

ListeLecteur insererEnTeteLec(ListeLecteur listeL, Lecteur lec, MaillonLecteur *m)
{
    m = (MaillonLecteur*)malloc(sizeof(MaillonLecteur));
    if (m == NULL) {
        printf("Problème malloc\n");
        exit(1);
    }

    m->l = lec;
    m->suivNum = listeL;

    return m;
}

ListeLecteur insererLecNum(ListeLecteur listeL, Lecteur lec, int *trouve, MaillonLecteur *m)
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

    listeL->suivNum = insererLecNum(listeL->suivNum, lec, trouve, m);
    *trouve = 0;
    return listeL;
}
ListeLecteur insererLecNom(ListeLecteur listeL, Lecteur lec, MaillonLecteur *m)
{
    if (listeL == NULL) {// liste vide
        m->suivNom = listeL;
        return listeL;
    }
    if ( strcmp(lec.nom, listeL->l.nom) < 0) {// lecteur > 1er liste nom
        m->suivNom = listeL;
        return listeL;
    }
    if ( strcmp(lec.nom, listeL->l.nom) == 0) { // lecteur == 1er list nom

        if ( strcmp(lec.prenom, listeL->l.prenom) < 0) {// lecteur > 1er liste nom
            m->suivNom = listeL;
            return listeL;
        }
        if ( strcmp(lec.prenom, listeL->l.prenom) == 0) { // lecteur == 1er liste meme prenom
            m->suivNom = listeL;
            return listeL;
        }
        if ( strcmp(lec.prenom, listeL->l.prenom) > 0) // lecteur > 1er liste meme prenom
            return insererLecNom(listeL->suivNom, lec, m);

    }

    listeL->suivNom = insererLecNom(listeL->suivNom, lec, m);
    return listeL;
}

ListeLecteur insererLec(ListeLecteur listeL, Lecteur lec)
{
    MaillonLecteur *m;
    int trouve;
    listeL = insererLecNum(listeL, lec, &trouve, m);

    if (trouve == 0)
        listeL = insererLecNom(listeL, lec, m);

    return listeL;
}
