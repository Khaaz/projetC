#include "projet.h"

//FONCTIONS POUR LES EMPRUNT

ListeEmprunt listeVideE(void)

{
	return NULL;
}

//fonctions de chargement du fichier emprunt

ListeEmprunt ChargementEmprunt(ListeEmprunt listeLEmp)

{
	Emprunt emp;
	FILE *flot;
	flot = fopen("emprunt.don", "r");
	if (flot == NULL)
	{
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	emp = lireEmprunt(flot);
	listeLEmp = insererEmprunt(listeLEmp, emp);
	while (!feof(flot))
	{
		emp = lireEmprunt(flot);
		listeLEmp = insererEmprunt(listeLEmp, emp);
	}
	fclose(flot);
	return listeLEmp;
}

Emprunt lireEmprunt(FILE *flot)

{
	Emprunt emp;
	fscanf(flot, "%s%*c\n", emp.cote);
	fscanf(flot, "%s%*c\n", emp.numLecteur);

	fscanf(flot, "%d/%d/%d%*c\n", &emp.dateEmprunt.jour, &emp.dateEmprunt.mois, &emp.dateEmprunt.annee);
	return emp;
}

//fonctions d'insertion d'un emprunt

ListeEmprunt ajouterEnTeteEmprunt(ListeEmprunt listeLEmp, Emprunt emp)

{
	MaillonEmprunt *m;
	m = (MaillonEmprunt *)malloc(sizeof(MaillonEmprunt));
	if (m == NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	m->e = emp;
	m->suivEmprunt = listeLEmp;
	return m;
}

ListeEmprunt insererEmprunt(ListeEmprunt listeLEmp, Emprunt emp)

{
	if (listeLEmp == NULL)
		return ajouterEnTeteEmprunt(listeLEmp, emp);
	if (strcmp(emp.cote, listeLEmp->e.cote) < 0)
		return ajouterEnTeteEmprunt(listeLEmp, emp);
	if (strcmp(emp.cote, listeLEmp->e.cote) == 0)
		return listeLEmp;
	listeLEmp->suivEmprunt = insererEmprunt(listeLEmp->suivEmprunt, emp);
	return listeLEmp;
}

ListeEmprunt insererClavierEmprunt(ListeEmprunt listeLEmp, Ouvrage **Touv, ListeLecteur listeLNum, int nbOuv)
{
	Emprunt emp;
	int rangOuv, trouve;
	printf("Référence de l'emprunteur ?\n");
	scanf("%s%*c", emp.numLecteur);
	trouve = ExisteNumLec(listeLNum, emp.numLecteur);
	if (trouve == 0)
	{
		printf("Lecteur introuvable");
		return listeLEmp;
	}
	printf("Cote de l'ouvrage ?\n");
	scanf("%s%*c", emp.cote);
	rangOuv = existeOuvrage(Touv, emp.cote, nbOuv);
	if (rangOuv == -1)
	{
		printf("ouvrage introuvable");
		return listeLEmp;
	}
	if (Touv[rangOuv]->dispo == faux)
	{
		printf("Ouvrage indisponible désolé");
		return listeLEmp;
	}
	printf("Date de l'emprunt ? (jj/mm/yyyy)\n");
	scanf("%d/%d/%d%*c", &(emp.dateEmprunt.jour), &(emp.dateEmprunt.mois), &(emp.dateEmprunt.annee));
	Touv[rangOuv]->dispo = faux;
	listeLEmp = insererEmprunt(listeLEmp, emp);

	return listeLEmp;
}

//fonction d'affichage de la liste des emprunts en cours

void afficherEmprunt(ListeEmprunt listeL)
{
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	printf("Cote\t\tLecteur\tdateEmprunt\n\n");
	while (listeL != NULL)
	{
		printf("%s\t%s\t%d/%d/%d\n", listeL->e.cote, listeL->e.numLecteur, listeL->e.dateEmprunt.jour, listeL->e.dateEmprunt.mois, listeL->e.dateEmprunt.annee);
		listeL = listeL->suivEmprunt;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

//Recherche ouvrage

int existeOuvrage(Ouvrage **Touv, char cote[], int nbOuv)
{
	int i;
	for (i = 0; i < nbOuv; i++)
	{
		if (strcmp(cote, Touv[i]->cote) == 0)
		{
			return i;
		}
	}
	return -1;
}

//fonctions de sauvegarde du fichier emprunt

void sauvegardeEmprunt(ListeEmprunt listeLEmp)

{
	FILE *flot;
	flot = fopen("emprunt.don", "w");
	if (flot == NULL)
	{
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	while (listeLEmp != NULL)
	{
		printEmprunt(listeLEmp, flot);
		listeLEmp = listeLEmp->suivEmprunt;
	}
	printf("\nFichier bien sauvegardé sous 'emprunt.don'\n");
	fclose(flot);
}

void printEmprunt(ListeEmprunt listeLEmp, FILE *flot)

{
	fprintf(flot, "%s\n", listeLEmp->e.cote);
	fprintf(flot, "%s\n", listeLEmp->e.numLecteur);
	fprintf(flot, "%d/%d/%d\n", listeLEmp->e.dateEmprunt.jour, listeLEmp->e.dateEmprunt.mois, listeLEmp->e.dateEmprunt.annee);
}

//fonction date de retour

ListeEmprunt RetourEmprunt(ListeEmprunt listeLEmp, Ouvrage **Touv, int nbOuv)
{
	ListeEmprunt aux;
	Date dateretour;
	int joursEmp, rangOuv;
	char cote[11], c;
	printf("Cote de l'ouvrage ?\n");
	scanf("%s%*c", cote);
	rangOuv = existeOuvrage(Touv, cote, nbOuv);
	if (rangOuv == -1)
	{
		printf("ouvrage introuvable");
		return listeLEmp;
	}
	if (Touv[rangOuv]->dispo == vrai)
	{
		printf("Ouvrage déja disponible");
		return listeLEmp;
	}
	aux = trouverEmprunt(listeLEmp, cote);
	printf("Date de retour ? (jj/mm/yyyy)\n");
	scanf("%d/%d/%d%*c", &(dateretour.jour), &(dateretour.mois), &(dateretour.annee));
	joursEmp = compareDate(listeLEmp->e.dateEmprunt, dateretour);
	while (joursEmp < 0)
	{
		printf("Date incohérente !! Date de retour ? (jj/mm/yyyy)\n");
		scanf("%d/%d/%d%*c", &(dateretour.jour), &(dateretour.mois), &(dateretour.annee));
		joursEmp = compareDate(listeLEmp->e.dateEmprunt, dateretour);
	}
	if (joursEmp > 15)
		printf("Délais de 15 jours non respecté ! Le lecteur doit payer une amande !");
	c = getchar();
	return SuppEmp(listeLEmp, cote);
}

//fonction compare date

int compareDate(Date d1, Date d2)
{
	int dateJ1, dateJ2, result;
	dateJ1 = (d1.jour) + ((d1.mois) * 30) + ((d1.annee) * 365);
	dateJ2 = (d2.jour) + ((d2.mois) * 30) + ((d2.annee) * 365);
	result = dateJ2 - dateJ1;
	return result;
}

ListeEmprunt trouverEmprunt(ListeEmprunt listeLEmp, char cote[])
{
	if (strcmp(cote, listeLEmp->e.cote) == 0)
		return listeLEmp;
	return trouverEmprunt(listeLEmp->suivEmprunt, cote);
}

//supprimer en tete

ListeEmprunt Suppentete(ListeEmprunt listeLEmp)
{
	MaillonEmprunt *aux;
	if (listeLEmp == NULL)
	{
		printf("OP interdite");
		exit(1);
	}
	aux = listeLEmp;
	listeLEmp = listeLEmp->suivEmprunt;
	free(aux);
	return listeLEmp;
}

ListeEmprunt SuppEmp(ListeEmprunt listeLEmp, char cote[])
{
	if (listeLEmp == NULL)
		return listeLEmp;
	if (strcmp(cote, listeLEmp->e.cote) == 0)
		return Suppentete(listeLEmp);
	listeLEmp->suivEmprunt = SuppEmp(listeLEmp->suivEmprunt, cote);
	return listeLEmp;
}