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
ListeLecteur ChargementLecteur(ListeLecteur listeLNum,ListeLecteur *listeLNom);
Lecteur lireLecteur(FILE *flot);
int Menu(void);
int ExisteNumLec(ListeLecteur listeLNum,char NumLecteur[]);
ListeLecteur insererLecNum(ListeLecteur listeL, MaillonLecteur *m, int *trouve);
ListeLecteur insererLecNom(ListeLecteur listeL , MaillonLecteur *m );
ListeLecteur insererLec(ListeLecteur listeLNum , ListeLecteur *listeLNom, Lecteur lec);
ListeLecteur ajouterLecteurAuClavier (Lecteur Lec,ListeLecteur listeLNum,ListeLecteur *listeLNom);
void afficherLec(ListeLecteur listeL , int menu );
void AffichInfosLec(ListeLecteur listeLNum);
ListeLecteur rechercheNum(char numLecteur[] , int *trouve , ListeLecteur listeLNum,char c);
ListeLecteur rechercheNom(char numLecteur[], ListeLecteur listeLNom );
ListeLecteur SupprimerGENERAL(ListeLecteur ListeLNum,ListeLecteur *ListeLNom);
ListeLecteur supprimerEnTete(ListeLecteur ListeASup,int idListe);
ListeLecteur supprimerLecNum(ListeLecteur ListeLNum , ListeLecteur listeApresRech );
ListeLecteur supprimerLecNom(ListeLecteur ListeLNom , ListeLecteur listeApresRech );
void sauvegardeLecteur(ListeLecteur listeLNum);
void printLecteur(ListeLecteur listeLNum,FILE *flot);
ListeLecteur menuModifAdresse(ListeLecteur listeLNum);
ListeLecteur modifAdresse(ListeLecteur listeLNum,ListeLecteur listeApresRech);
Adresse rentrerAdresse(ListeLecteur listeLNum);

