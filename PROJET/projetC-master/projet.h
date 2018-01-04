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
    char cote[11];
    char numLecteur[6];
    Date dateEmprunt;
    Date *dateRetour;
} Emprunt;

typedef struct {
    char numLecteur[6];
    char nom[30];
    char prenom[30];
    Adresse adresse;
    Emprunt *TabEmprunt[4]; //tableau qui liste les emprunts
} Lecteur;

typedef struct {
    char cote[11];
    char titre[30];
    char categorie[30];
    Booleen dispo; // Ouvrage dispo ou pas
    Emprunt *e; // si ouvrage non dispo ==> donnée de l'emprunt
} Ouvrage;



//listes

typedef struct maillonLecteur {
    Lecteur l;
    struct maillonLecteur *suivNum;
    struct maillonLecteur *suivNom;
} MaillonLecteur, *ListeLecteur;



// liste fonctions

ListeLecteur listeVide(void);
ListeLecteur insererLecNum(ListeLecteur listeL, MaillonLecteur *m, int *trouve);
ListeLecteur insererLecNom(ListeLecteur listeL , MaillonLecteur *m );
ListeLecteur insererLec(ListeLecteur listeLNum , ListeLecteur *listeLNom, Lecteur lec);
void afficherLec(ListeLecteur listeL , int menu );
ListeLecteur rechercheNum(char numLecteur[] , int *trouve , ListeLecteur listeLNum , char c);
ListeLecteur rechercheNom(char numLecteur[], ListeLecteur listeLNom );
ListeLecteur supprimer1(ListeLecteur listeL , ListeLecteur listeApresRech );
ListeLecteur supprimer2(ListeLecteur listeL , ListeLecteur listeApresRech );

