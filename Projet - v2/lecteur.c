#include "projet.h"

//FONCTIONS POUR LES LECTEURS

// initialisation
//
ListeLecteur listeVide(void)
{
	return NULL;
}

// chargement
//
ListeLecteur ChargementLecteur(ListeLecteur listeLNum, ListeLecteur *listeLNom)
{
	//var
	Lecteur Lec;
	FILE *flot;
	//
	flot = fopen("lecteur.don", "r");
	if (flot == NULL)
	{
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	Lec = lireLecteur(flot);
	listeLNum = insererLec(listeLNum, listeLNom, Lec);
	while (!feof(flot))
	{
		Lec = lireLecteur(flot);
		listeLNum = insererLec(listeLNum, listeLNom, Lec);
	}
	fclose(flot);
	return listeLNum;
}

Lecteur lireLecteur(FILE *flot)
{
	//var
	Lecteur Lec;
	//
	fscanf(flot, "%s\n", Lec.numLecteur);

	fgets(Lec.nom, 28, flot);
	Lec.nom[strlen(Lec.nom) - 1] = '\0';

	fscanf(flot, "%s\n", Lec.prenom);

	fscanf(flot, "%d\t", &(Lec.adresse.numRue));

	fgets(Lec.adresse.nomRue, 28, flot);
	Lec.adresse.nomRue[strlen(Lec.adresse.nomRue) - 1] = '\0';

	fscanf(flot, "%s\n", Lec.adresse.ville);

	fscanf(flot, "%d\n", &(Lec.adresse.numDepartement));
	return Lec;
}

ListeLecteur insererLec(ListeLecteur listeLNum, ListeLecteur *listeLNom, Lecteur lec) //inserer lecteur dans une liste a deux poiteurs
{
	//var
	MaillonLecteur *m;
	int trouve = 0;
	//
	m = (MaillonLecteur *)malloc(sizeof(MaillonLecteur));
	if (m == NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	m->l = lec;
	listeLNum = insererLecNum(listeLNum, m, &trouve);

	if (trouve == 0)
	{
		*listeLNom = insererLecNom(*listeLNom, m);
	}
	else
		free(m);

	return listeLNum;
}

ListeLecteur insererLecNum(ListeLecteur listeL, MaillonLecteur *m, int *trouve)
{
	if (listeL == NULL)
	{
		m->suivNum = NULL;
		return m;
	}
	if (strcmp(m->l.numLecteur, listeL->l.numLecteur) < 0)
	{
		m->suivNum = listeL;
		return m;
	}
	if (strcmp(m->l.numLecteur, listeL->l.numLecteur) == 0)
	{
		*trouve = 1;
		return listeL;
	}

	listeL->suivNum = insererLecNum(listeL->suivNum, m, trouve);
	return listeL;
}

ListeLecteur insererLecNom(ListeLecteur listeL, MaillonLecteur *m)
{
	if (listeL == NULL)
	{
		m->suivNom = NULL;
		return m;
	}
	if (strcmp(m->l.nom, listeL->l.nom) < 0)
	{
		m->suivNom = listeL;
		return m;
	}
	if (strcmp(m->l.nom, listeL->l.nom) == 0)
	{

		if (strcmp(m->l.prenom, listeL->l.prenom) <= 0)
		{
			m->suivNom = listeL;
			return m;
		}
		return listeL;
	}

	listeL->suivNom = insererLecNom(listeL->suivNom, m);
	return listeL;
}

// Insertion
//
ListeLecteur ajouterLecteurAuClavier(ListeLecteur listeLNum, ListeLecteur *listeLNom)
{
	//var
	int choix, trouve;
	Lecteur Lec;
	//
	printf("Nom ?\n");
	fgets(Lec.nom, 28, stdin);
	Lec.nom[strlen(Lec.nom) - 1] = '\0';

	printf("Prénom ?\n");
	fgets(Lec.prenom, 28, stdin);
	Lec.prenom[strlen(Lec.prenom) - 1] = '\0';

	printf("Numéro de département ?\n");
	scanf("%d%*c", &(Lec.adresse.numDepartement));

	printf("Ville ?\n");
	fgets(Lec.adresse.ville, 28, stdin);
	Lec.adresse.ville[strlen(Lec.adresse.ville) - 1] = '\0';

	printf("Nom de la rue ?\n");
	fgets(Lec.adresse.nomRue, 28, stdin);
	Lec.adresse.nomRue[strlen(Lec.adresse.nomRue) - 1] = '\0';

	printf("Numéro du domicile ?\n");
	scanf("%d", &(Lec.adresse.numRue));

	printf("Numéro de lecteur ?\n");
	scanf("%s", Lec.numLecteur);

	printf("\n--- RESUME ---\n");

	printf("%s\t%s\t%s\t%d %s %s %d\n", Lec.numLecteur, Lec.nom, Lec.prenom, Lec.adresse.numRue, Lec.adresse.nomRue, Lec.adresse.ville, Lec.adresse.numDepartement);

	printf("Voulez vous entrer ce lecteur ? (0=Oui 1=Non) \n");
	scanf("%d%*c", &choix);
	if (choix == 0)
	{
		trouve = ExisteNumLec(listeLNum, Lec.numLecteur);
		if (trouve == 0)
		{
			listeLNum = insererLec(listeLNum, listeLNom, Lec);
			printf("\n--- LECTEUR ENREGISTRE ---\n");
		}
		else
			printf("\n--- LECTEUR NON ENREGISTRE CAR NUMERO DE LECTEUR EXISTE DEJA ---\n");
	}
	return listeLNum;
}

int ExisteNumLec(ListeLecteur listeLNum, char NumLecteur[])
{
	if (listeLNum == NULL)
		return 0;
	if (strcmp(NumLecteur, listeLNum->l.numLecteur) == 0)
		return 1;
	return ExisteNumLec(listeLNum->suivNum, NumLecteur);
}

//Suppresion
//
ListeLecteur SupprimerGENERAL(ListeLecteur ListeLNum, ListeLecteur *ListeLNom)
{
	//var
	char NumLecRech[6], c;
	int trouve, choix;
	ListeLecteur aux1, aux2;
	// 
	printf("\n\tNuméro de Lecteur ?\n");
	scanf("%s", NumLecRech);

	aux1 = rechercheNum(NumLecRech, &trouve, ListeLNum, c);
	if (trouve == 1)
	{
		printf("\nEtes vous sûr de vouloir supprimer ce lecteur (0=Oui/1=Non)\n");
		scanf("%d%*c", &choix);
		if (choix == 0)
		{
			aux2 = rechercheNom(NumLecRech, *ListeLNom);
			ListeLNum = supprimerLecNum(ListeLNum, aux1);
			*ListeLNom = supprimerLecNom(*ListeLNom, aux2);
			printf("\n--- LECTEUR CORRECTEMENT SUPPRIME ---\n");
		}
		else
			printf("\n--- LECTEUR NON SUPPRIME ---\n");
	}
	return ListeLNum;
}

ListeLecteur rechercheNum(char numLecteur[], int *trouve, ListeLecteur listeLNum, char c)
{

	if (listeLNum == NULL)
	{
		printf("\nLecteur introuvable\n");
		c = getchar();
		*trouve = 0;
		return listeLNum;
	}
	if (strcmp(numLecteur, listeLNum->l.numLecteur) == 0)
	{
		*trouve = 1;
		printf("--- LECTEUR TROUVE ---\n\n%s\t%s\t%s\t%d %s %s %d\n", listeLNum->l.numLecteur, listeLNum->l.nom, listeLNum->l.prenom, listeLNum->l.adresse.numRue, listeLNum->l.adresse.nomRue, listeLNum->l.adresse.ville, listeLNum->l.adresse.numDepartement);
		c = getchar();
		return listeLNum;
	}
	return rechercheNum(numLecteur, trouve, listeLNum->suivNum, c);
}

ListeLecteur rechercheNom(char numLecteur[], ListeLecteur listeLNom)
{
	if (strcmp(numLecteur, listeLNom->l.numLecteur) == 0)
		return listeLNom;
	return rechercheNom(numLecteur, listeLNom->suivNom);
}

ListeLecteur supprimerLecNum(ListeLecteur ListeLNum, ListeLecteur listeApresRech) //suppresion num
{
	if (ListeLNum == listeApresRech)
		return supprimerEnTete(ListeLNum, 0);
	ListeLNum->suivNum = supprimerLecNum(ListeLNum->suivNum, listeApresRech);
	return ListeLNum;
}

ListeLecteur supprimerLecNom(ListeLecteur ListeLNom, ListeLecteur listeApresRech) //suppresion nom
{
	if (ListeLNom == listeApresRech)
		return supprimerEnTete(ListeLNom, 1);
	ListeLNom->suivNom = supprimerLecNom(ListeLNom->suivNom, listeApresRech);
	return ListeLNom;
}

ListeLecteur supprimerEnTete(ListeLecteur ListeASup, int idListe)
{
	//var
	MaillonLecteur *aux;
	//
	if (ListeASup == NULL)
	{
		printf("Opération impossible\n");
		exit(1);
	}
	aux = ListeASup;
	if (idListe == 0)
		ListeASup = ListeASup->suivNum;
	else
	{
		ListeASup = ListeASup->suivNom;
		free(aux);
	}
	return ListeASup;
}

// Affichage 1 lecteur
//
void AffichInfosLec(ListeLecteur listeLNum)
{
	//var
	ListeLecteur aux;
	char NumLecRech[6], c;
	int trouve;
	//
	printf("Numéro de Lecteur ?\n");
	scanf("%s", NumLecRech);
	aux = rechercheNum(NumLecRech, &trouve, listeLNum, c);
}

// Affichage all lecteurs
//
void afficherLec(ListeLecteur listeL, int menu)
{
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	while (listeL != NULL)
	{
		printf("%s\t%s\t%s\t%d %s %s %d\n", listeL->l.numLecteur, listeL->l.nom, listeL->l.prenom, listeL->l.adresse.numRue, listeL->l.adresse.nomRue, listeL->l.adresse.ville, listeL->l.adresse.numDepartement);
		if (menu == 4)
			listeL = listeL->suivNom;
		else
			listeL = listeL->suivNum;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

// Sauvegarde
//
void sauvegardeLecteur(ListeLecteur listeLNum)
{
	//var
	FILE *flot;
	//
	flot = fopen("lecteur.don", "w");
	if (flot == NULL)
	{
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	while (listeLNum != NULL)
	{
		printLecteur(listeLNum, flot);
		listeLNum = listeLNum->suivNum;
	}
	printf("\nFichier bien sauvegardé sous 'lecteur.don'\n");
	fclose(flot);
}

void printLecteur(ListeLecteur listeLNum, FILE *flot)
{
	fprintf(flot, "%s\n", listeLNum->l.numLecteur);
	fprintf(flot, "%s\n", listeLNum->l.nom);
	fprintf(flot, "%s\n", listeLNum->l.prenom);
	fprintf(flot, "%d\t", listeLNum->l.adresse.numRue);
	fprintf(flot, "%s\n", listeLNum->l.adresse.nomRue);
	fprintf(flot, "%s\n", listeLNum->l.adresse.ville);
	fprintf(flot, "%d\n", listeLNum->l.adresse.numDepartement);
}

// Modification address
//
ListeLecteur menuModifAdresse(ListeLecteur listeLNum)
{
	//var
	char NumLecRech[6], c;
	int trouve;
	ListeLecteur aux1;
	//
	printf("\nDe quel lecteur voulez vous modifier l'adresse (Entrez son numéro de lecteur :)\n");
	scanf("%s", NumLecRech);
	aux1 = rechercheNum(NumLecRech, &trouve, listeLNum, c);
	if (trouve == 1)
	{
		listeLNum = modifAdresse(listeLNum, aux1);
		printf("\nLes modifications de l'adresse du client %s ont bien été effectuées !\n", NumLecRech);
	}
	return listeLNum;
}

ListeLecteur modifAdresse(ListeLecteur listeLNum, ListeLecteur listeApresRech)
{
	if (listeLNum == listeApresRech)
	{
		listeLNum->l.adresse = rentrerAdresse(listeLNum);
		return listeLNum;
	}
	listeLNum->suivNum = modifAdresse(listeLNum->suivNum, listeApresRech);
}

Adresse rentrerAdresse(ListeLecteur listeLNum)
{
	//var
	Adresse a;
	//
	printf("Nouvelle ville :\n");
	fgets(a.ville, 28, stdin);
	a.ville[strlen(a.ville) - 1] = '\0';

	printf("Nouveau numéro de domicile :\n");
	scanf("%d%*c", &a.numRue);

	printf("Nouveau nom de la rue :\n");
	fgets(a.nomRue, 28, stdin);
	a.nomRue[strlen(a.nomRue) - 1] = '\0';

	printf("Nouveau numéro de département :\n");
	scanf("%d%*c", &a.numDepartement);
	return a;
}
