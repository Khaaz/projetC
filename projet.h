#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*

system("date >> date.txt")


*/

//struct generale
typedef enum {faux, vrai} Booleen;

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    int numRue;
    char nomRue[30];
    char ville[30];
    int numDepartement;
} Adresse;


// specifique
typedef struct {
    char numLecteur[6];
    char nom[30];
    char prenom[30];
    Adresse *adresse;
    Emprunt *TabEmprunt[4]; //tableau qui liste les emprunts
} Lecteur;

typedef struct {
    char cote[11];
    char titre[30];
    char categorie[30];
    Boolen dispo; // Ouvrage dispo ou pas
    Emprunt *e; // si ouvrage non dispo ==> donnée de l'emprunt
} Ouvrage;

typedef struct {
    char cote[11];
    Lecteur l;
    Date dateEmprunt;
    Date *dateRetour;
} Emprunt;

//listes

typedef struct maillonLecteur {
    Lecteur l;
    struct maillonLecteur *suivNum;
    struct maillonLecteur *suivNom;
} MaillonLecteur, *ListeLecteur;



// liste fonctions

ListeLecteur listeVide (void);
ListeLecteur insererEnTeteLec(ListeLecteur listeL, Lecteur lec, MaillonLecteur *m);
ListeLecteur insererLecNum(ListeLecteur listeL, Lecteur lec, int *trouve, MaillonLecteur *m);
ListeLecteur insererLecNom(ListeLecteur listeL, Lecteur lec, MaillonLecteur *m);
ListeLecteur insererLec(ListeLecteur listeL, Lecteur lec);


