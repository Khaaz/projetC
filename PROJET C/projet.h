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
    Emprunt *TabEmprunt[4]; //tableau qui liste les emprunts en cours
} Lecteur;

typedef struct {
    char cote[11];
    char titre[30];
    char categorie[30];
    Booleen dispo; // Ouvrage dispo ou pas
    Emprunt *e; // si ouvrage non dispo ==> donnée de l'emprunt en cours
} Ouvrage;



//listes

typedef struct maillonLecteur {
    Lecteur l;
    struct maillonLecteur *suivNum;
    struct maillonLecteur *suivNom;
} MaillonLecteur, *ListeLecteur;



// LISTE FONCTIONS

//FONCTIONS LECTEUR(+MENUS)
ListeLecteur listeVide(void);
ListeLecteur ChargementLecteur(ListeLecteur listeLNum,ListeLecteur *listeLNom);
Lecteur lireLecteur(FILE *flot);
int MenuPRINCIPAL(void);
int MenuLecteur(void);
int MenuOuvrage(void);
int MenuEmprunt(void);
int ExisteNumLec(ListeLecteur listeLNum,char NumLecteur[]);
ListeLecteur insererLecNum(ListeLecteur listeL, MaillonLecteur *m, int *trouve);
ListeLecteur insererLecNom(ListeLecteur listeL , MaillonLecteur *m );
ListeLecteur insererLec(ListeLecteur listeLNum , ListeLecteur *listeLNom, Lecteur lec);
ListeLecteur ajouterLecteurAuClavier (ListeLecteur listeLNum,ListeLecteur *listeLNom);
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
//FONCTIONS OUVRAGE
Ouvrage **ChargementOuvrage(int *tmax,int *nb);
Ouvrage lireOuvrage(FILE *flot);
void afficherOuvrage(Ouvrage **Touv,int nb);
int rechercheDichotomie(Ouvrage **tab,int nb,char coteRech[]);
Ouvrage **insererOuvrage(Ouvrage **Touv,int *nb,int *tmax);
Ouvrage **decalerAdroite(Ouvrage **Touv,int pos,int nb);
Ouvrage ajouterOuvrageAuClavier(void);
void sauvegardeOuvrage(Ouvrage **Touv,int nb);
void printOuvrage(Ouvrage **Touv,FILE *flot,int i);
//FONCTIONS EMPRUNT
