#include "projet.h"

//fonctions d'affichage des différents menu

int MenuPRINCIPAL(void)
{
	int choixM, menu;
	//
	printf("\n1) Menu Lecteur\n2) Menu Ouvrage\n3) Menu Emprunt\n0) QUITTER\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c", &choixM);
	return choixM;
}

int MenuLecteur(void)
{
	int menu;
	//
	printf("\n1) Insérer un nouveau lecteur\n2) Supprimer lecteur\n3) Afficher les informations d'un lecteur \n4) Affichage des lecteurs par ordre alphabétique\n5) Affichage des lecteurs selon leur identifiant de lecteur\n6) Sauvegarder le fichier des lecteurs\n7) Modifier une adresse\n0) REVENIR AU MENU PRINCIPAL\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c", &menu);
	return menu;
}

int MenuOuvrage(void)
{
	int menu;
	//
	printf("\n1) Insérer un nouvel ouvrage\n2) Afficher la liste des ouvrages\n3) Sauvegarder le fichier des ouvrages\n0) REVENIR AU MENU PRINCIPAL\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c", &menu);
	return menu;
}

int MenuEmprunt(void)
{
	int menu;
	//
	printf("\n1) Enregistrer un nouvel emprunt\n2) Consulter la liste des emprunts en cours\n3) Enregistrer une date de retour\n4) Sauvegarder le fichier des emprunts et des ouvrages\n0) REVENIR AU MENU PRINCIPAL\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c", &menu);
	return menu;
}
