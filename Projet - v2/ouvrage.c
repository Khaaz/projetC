#include "projet.h"

//FONCTIONS POUR LES OUVRAGES

//fonctions de chargement du fichier ouvrage dans un tableau dynamique de pointeurs

Ouvrage **ChargementOuvrage(int *tmax, int *nb)

{
	Ouvrage **Touv, o, **aux;
	FILE *flot;
	flot = fopen("ouvrage.don", "r");
	if (flot == NULL)
	{
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	*nb = 0;
	*tmax = 5;
	Touv = (Ouvrage **)malloc(*tmax * sizeof(Ouvrage *));
	if (Touv == NULL)
	{
		printf("Problème malloc\n");
		fclose(flot);
		exit(1);
	}
	o = lireOuvrage(flot);
	while (!feof(flot))
	{
		if (*nb == *tmax)
		{
			*tmax = *tmax + 5;
			aux = (Ouvrage **)realloc(Touv, *tmax * sizeof(Ouvrage *));
			if (aux == NULL)
			{
				printf("Problème malloc\n");
				fclose(flot);
				exit(1);
			}
			Touv = aux;
		}
		Touv[*nb] = (Ouvrage *)malloc(sizeof(Ouvrage));
		if (Touv[*nb] == NULL)
		{
			printf("Problème malloc\n");
			fclose(flot);
			exit(1);
		}
		*Touv[*nb] = o;
		*nb = *nb + 1;
		o = lireOuvrage(flot);
	}
	fclose(flot);
	return Touv;
}

Ouvrage lireOuvrage(FILE *flot)

{
	Ouvrage o;
	char Dispo[15];
	fscanf(flot, "%s\n", o.cote);

	fgets(o.titre, 28, flot);
	o.titre[strlen(o.titre) - 1] = '\0';

	fgets(o.categorie, 28, flot);
	o.categorie[strlen(o.categorie) - 1] = '\0';

	fscanf(flot, "%s", Dispo);
	if (strcmp(Dispo, "dispo") == 0)
		o.dispo = vrai;
	else
		o.dispo = faux;
	return o;
}

//fonctions d'insertion d'un ouvrage

int rechercheDichotomie(Ouvrage **tab, int nb, char coteRech[])

{
	int inf, sup, m;
	inf = 0;
	sup = nb - 1;
	while (inf <= sup)
	{
		m = (inf + sup) / 2;
		if (strcmp(coteRech, tab[m]->cote) == 0)
			return -1;
		if (strcmp(coteRech, tab[m]->cote) > 0)
			inf = m + 1;
		else
			sup = m - 1;
	}
	return inf;
}

Ouvrage **insererOuvrage(Ouvrage **Touv, int *nb, int *tmax)

{
	Ouvrage o, **aux;
	int posInsertion, choix;
	o = ajouterOuvrageAuClavier();
	posInsertion = rechercheDichotomie(Touv, *nb, o.cote);
	if (posInsertion == -1)
	{
		printf("\n--- ERREUR : UN OUVRAGE PORTE DEJA LA MEME COTE INSERTION IMPOSSIBLE ---\n");
		return Touv;
	}
	printf("\n%s\t%s\t%s", o.cote, o.titre, o.categorie);
	printf("\nEtes vous sûr de vouloir ajouter cet ouvrage ? (0=Oui/1=Non)\n");
	scanf("%d%*c", &choix);
	if (choix == 1)
	{
		printf("\n--- INSERTION ANNULEE ---\n");
		return Touv;
	}
	if (*nb == *tmax)
	{
		*tmax = *tmax + 5;
		aux = (Ouvrage **)realloc(Touv, *tmax * sizeof(Ouvrage *));
		if (aux == NULL)
		{
			printf("Problème malloc\n");
			exit(1);
		}
		Touv = aux;
	}
	Touv[*nb] = (Ouvrage *)malloc(sizeof(Ouvrage));
	if (Touv[*nb] == NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	Touv = decalerAdroite(Touv, posInsertion, *nb);
	*Touv[posInsertion] = o;
	*nb = *nb + 1;
	printf("\n--- INSERTION CORRECTEMENT EFFECTUEE ---\n");
	return Touv;
}

Ouvrage **decalerAdroite(Ouvrage **Touv, int pos, int nb)

{
	for (nb; nb > pos; nb--)
		*Touv[nb] = *Touv[nb - 1];
	return Touv;
}

Ouvrage ajouterOuvrageAuClavier(void)

{
	Ouvrage o;

	printf("Côte de l'ouvrage :\n");
	scanf("%s%*c", o.cote);

	printf("Titre de l'ouvrage :\n");
	fgets(o.titre, 28, stdin);
	o.titre[strlen(o.titre) - 1] = '\0';

	printf("Catégorie de l'ouvrage :\n");
	fgets(o.categorie, 28, stdin);
	o.categorie[strlen(o.categorie) - 1] = '\0';

	o.dispo = vrai;
	return o;
}

//fonctions d'affichage de la liste des livres de la bibliothèque

void afficherOuvrage(Ouvrage **Touv, int nb)

{
	int i;
	for (i = 0; i < nb; i++)
		printf("%s\t\t%s\t\t%s\n", Touv[i]->cote, Touv[i]->titre, Touv[i]->categorie);
}

//fonctions de sauvegarde du fichier ouvrage

void sauvegardeOuvrage(Ouvrage **Touv, int nb)

{
	int i = 0;
	FILE *flot;
	flot = fopen("ouvrage.don", "w");
	if (flot == NULL)
	{
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	while (i != nb)
	{
		printOuvrage(Touv, flot, i);
		i = i + 1;
	}
	printf("\nFichier bien sauvegardé sous 'ouvrage.don'\n");
	fclose(flot);
}

void printOuvrage(Ouvrage **Touv, FILE *flot, int i)

{
	fprintf(flot, "%s\n", Touv[i]->cote);
	fprintf(flot, "%s\n", Touv[i]->titre);
	fprintf(flot, "%s\n", Touv[i]->categorie);
	if (Touv[i]->dispo == vrai)
		fprintf(flot, "dispo\n");
	else
		fprintf(flot, "emprunte\n");
}