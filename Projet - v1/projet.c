#include "projet.h"

//FONCTIONS POUR LES LECTEURS

// fonction d'initialisation de Liste Lecteur

ListeLecteur listeVide (void)
{
    return NULL;
}

//fonctions de chargement des lecteurs dans une liste

ListeLecteur ChargementLecteur(ListeLecteur listeLNum,ListeLecteur *listeLNom)

{
	Lecteur Lec;
	FILE *flot;
	flot=fopen("lecteur.don","r");
	if (flot==NULL)
	{
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	Lec=lireLecteur(flot);
	listeLNum=insererLec(listeLNum ,listeLNom ,Lec);
	while(!feof(flot))
	{
		Lec=lireLecteur(flot);
		listeLNum=insererLec(listeLNum ,listeLNom ,Lec);
	}
	fclose(flot);
	return listeLNum;
}

Lecteur lireLecteur(FILE *flot)

{
	Lecteur Lec;

	fscanf(flot,"%s\n",Lec.numLecteur);

	fgets(Lec.nom,28,flot);
	Lec.nom[strlen(Lec.nom)-1]='\0';

	fscanf(flot,"%s\n",Lec.prenom);

	fscanf(flot,"%d\t",&(Lec.adresse.numRue));

	fgets(Lec.adresse.nomRue,28,flot);
	Lec.adresse.nomRue[strlen(Lec.adresse.nomRue)-1]='\0';

	fscanf(flot,"%s\n",Lec.adresse.ville);

	fscanf(flot,"%d\n",&(Lec.adresse.numDepartement));
	return Lec;
}

//fonctions d'affichage des différents menu

int MenuPRINCIPAL(void)

{
	int choixM,menu;
	printf("\n1) Menu Lecteur\n2) Menu Ouvrage\n3) Menu Emprunt\n0) QUITTER\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c",&choixM);
	return choixM;
}


int MenuLecteur(void)

{
	int menu;
	printf("\n1) Insérer un nouveau lecteur\n2) Supprimer lecteur\n3) Afficher les informations d'un lecteur \n4) Affichage des lecteurs par ordre alphabétique\n5) Affichage des lecteurs selon leur identifiant de lecteur\n6) Sauvegarder le fichier des lecteurs\n7) Modifier une adresse\n0) REVENIR AU MENU PRINCIPAL\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c",&menu);
	return menu;
}

int MenuOuvrage(void)

{
	int menu;
	printf("\n1) Insérer un nouvel ouvrage\n2) Afficher la liste des ouvrages\n3) Sauvegarder le fichier des ouvrages\n0) REVENIR AU MENU PRINCIPAL\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c",&menu);
	return menu;
}

int MenuEmprunt(void)

{
	int menu;
	printf("\n1) Enregistrer un nouvel emprunt\n2) Consulter la liste des emprunts en cours\n3) Enregistrer une date de retour\n4) Sauvegarder le fichier des emprunts\n0) REVENIR AU MENU PRINCIPAL\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c",&menu);
	return menu;
}

//fonctions d'insertion d'un lecteur dans une liste à 2 pointeurs

int ExisteNumLec(ListeLecteur listeLNum,char NumLecteur[])

{	
	if(listeLNum==NULL)
		return 0;
	if(strcmp(NumLecteur, listeLNum->l.numLecteur) == 0)
		return 1;
	return ExisteNumLec(listeLNum->suivNum , NumLecteur);
}
	


ListeLecteur insererLecNum(ListeLecteur listeL, MaillonLecteur *m, int *trouve)
{
    if (listeL == NULL)
		{
		m->suivNum = NULL ;
		return m;
		}
    if ( strcmp(m->l.numLecteur, listeL->l.numLecteur) < 0)
        	{
		m->suivNum = listeL ;
		return m;
		}
    if ( strcmp(m->l.numLecteur, listeL->l.numLecteur) == 0) 
    {
        *trouve = 1;
        return listeL;
    }

    listeL->suivNum = insererLecNum(listeL->suivNum , m , trouve);
    return listeL;
}

ListeLecteur insererLecNom(ListeLecteur listeL , MaillonLecteur *m )
{
	if (listeL == NULL)
		{
		m->suivNom = NULL ;
		return m;
		}
    	if ( strcmp(m->l.nom, listeL->l.nom) < 0)
        {
		m->suivNom = listeL ;
		return m;
	}
    	if ( strcmp(m->l.nom, listeL->l.nom) == 0) 
	{

    		if ( strcmp(m->l.prenom, listeL->l.prenom) <= 0)
        	{
			m->suivNom = listeL ;
			return m;
		}
        	return listeL;
    	}

    listeL->suivNom = insererLecNom(listeL->suivNom , m );
    return listeL;
		
}


ListeLecteur insererLec(ListeLecteur listeLNum ,ListeLecteur *listeLNom , Lecteur lec)
{
    MaillonLecteur *m;
    int trouve=0;
    m = (MaillonLecteur*)malloc(sizeof(MaillonLecteur));
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

ListeLecteur ajouterLecteurAuClavier (ListeLecteur listeLNum,ListeLecteur *listeLNom)

{
	int choix,trouve;
	Lecteur Lec;
	
	printf("Nom ?\n");
	fgets(Lec.nom,28,stdin);
	Lec.nom[strlen(Lec.nom)-1]='\0';

	printf("Prénom ?\n");
	fgets(Lec.prenom,28,stdin);
	Lec.prenom[strlen(Lec.prenom)-1]='\0';

	printf("Numéro de département ?\n");
	scanf("%d%*c",&(Lec.adresse.numDepartement));

	printf("Ville ?\n");
	fgets(Lec.adresse.ville,28,stdin);
	Lec.adresse.ville[strlen(Lec.adresse.ville)-1]='\0';

	printf("Nom de la rue ?\n");
	fgets(Lec.adresse.nomRue,28,stdin);
	Lec.adresse.nomRue[strlen(Lec.adresse.nomRue)-1]='\0';

	printf("Numéro du domicile ?\n");
	scanf("%d",&(Lec.adresse.numRue));

	printf("Numéro de lecteur ?\n");
	scanf("%s",Lec.numLecteur);

	printf("\n--- RESUME ---\n");
					 
	printf("%s\t%s\t%s\t%d %s %s %d\n",Lec.numLecteur,Lec.nom, Lec.prenom,Lec.adresse.numRue, Lec.adresse.nomRue, Lec.adresse.ville, Lec.adresse.numDepartement);

	printf("Voulez vous entrer ce lecteur ? (0=Oui 1=Non) \n");
	scanf("%d%*c",&choix);
	if (choix==0)
	{
		trouve=ExisteNumLec(listeLNum,Lec.numLecteur);
		listeLNum = insererLec(listeLNum, listeLNom , Lec);
		if (trouve==0)
			printf("\n--- LECTEUR ENREGISTRE ---\n");
		else 
			printf("\n--- LECTEUR NON ENREGISTRE CAR NUMERO DE LECTEUR EXISTE DEJA ---\n");
	}
	return listeLNum;
}

//fonctions d'affichage d'informations sur les lecteurs

void afficherLec(ListeLecteur listeL,int menu)
{
    printf("\n-----------------------------------------------------------------------------------------------------\n");
    while(listeL != NULL )
		{
    	printf("%s\t%s\t%s\t%d %s %s %d\n",listeL->l.numLecteur,listeL->l.nom, listeL->l.prenom, listeL->l.adresse.numRue, listeL->l.adresse.nomRue, listeL->l.adresse.ville, listeL->l.adresse.numDepartement);
		if (menu==4)
    		listeL=listeL->suivNom;
		else
			listeL=listeL->suivNum;
		}
    printf("-----------------------------------------------------------------------------------------------------\n");

}

void AffichInfosLec(ListeLecteur listeLNum)

{
	ListeLecteur aux;
	char NumLecRech[6],c;
	int trouve;
	printf("Numéro de Lecteur ?\n");
	scanf("%s",NumLecRech);
	aux=rechercheNum(NumLecRech,&trouve,listeLNum,c) ;
}

//fonctions de suppression d'un lecteur dans une liste à 2 pointeurs

ListeLecteur rechercheNum(char numLecteur[], int *trouve , ListeLecteur listeLNum,char c)
{
	
	if(listeLNum==NULL)
		{
		printf("\nLecteur introuvable\n");
		c=getchar();
		*trouve=0;
		return listeLNum;
		}
	if(strcmp(numLecteur, listeLNum->l.numLecteur) == 0)
		{
		*trouve=1;
		printf("--- LECTEUR TROUVE ---\n\n%s\t%s\t%s\t%d %s %s %d\n",listeLNum->l.numLecteur,listeLNum->l.nom, listeLNum->l.prenom, listeLNum->l.adresse.numRue, listeLNum->l.adresse.nomRue, listeLNum->l.adresse.ville, listeLNum->l.adresse.numDepartement);
		c=getchar();
		return listeLNum;
		}
	return rechercheNum(numLecteur , trouve , listeLNum->suivNum,c);
}

ListeLecteur rechercheNom(char numLecteur[], ListeLecteur listeLNom )
{
	if(strcmp(numLecteur, listeLNom->l.numLecteur) == 0)
		return listeLNom;
	return rechercheNom(numLecteur , listeLNom->suivNom);
}
	
ListeLecteur SupprimerGENERAL(ListeLecteur ListeLNum,ListeLecteur *ListeLNom)

{
	char NumLecRech[6],c;
	int trouve,choix;
	ListeLecteur aux1,aux2;
	printf("\n\tNuméro de Lecteur ?\n");
	scanf("%s",NumLecRech);

	aux1=rechercheNum(NumLecRech,&trouve,ListeLNum,c) ;
	if (aux1!=NULL)
		aux2=rechercheNom(NumLecRech,*ListeLNom);

	if(trouve==1)
	{	
		printf("\nEtes vous sûr de vouloir supprimer ce lecteur (0=Oui/1=Non)\n");
		scanf("%d%*c",&choix);
		if (choix==0)
		{
			ListeLNum=supprimerLecNum(ListeLNum,aux1);
			*ListeLNom=supprimerLecNom(*ListeLNom,aux2);
			printf("\n--- LECTEUR CORRECTEMENT SUPPRIME ---\n");
		}
		else printf("\n--- LECTEUR NON SUPPRIME ---\n");
	}
	return ListeLNum;
}
	
ListeLecteur supprimerEnTete(ListeLecteur ListeASup,int idListe)

{
	MaillonLecteur *aux;
	if (ListeASup==NULL)
	{
		printf("Opération impossible\n");
		exit(1);
	}
	aux=ListeASup;
	if (idListe==0)
		ListeASup=ListeASup->suivNum;
	else
	{
		ListeASup=ListeASup->suivNom;
		free(aux);
	}
	return ListeASup;
}


ListeLecteur supprimerLecNum(ListeLecteur ListeLNum , ListeLecteur listeApresRech )
{
	if(ListeLNum==listeApresRech)
		return supprimerEnTete(ListeLNum,0);
	ListeLNum->suivNum=supprimerLecNum(ListeLNum->suivNum , listeApresRech );
	return ListeLNum;
}

ListeLecteur supprimerLecNom(ListeLecteur ListeLNom , ListeLecteur listeApresRech )
{
	if(ListeLNom==listeApresRech)
		return supprimerEnTete(ListeLNom,1);
	ListeLNom->suivNom=supprimerLecNom(ListeLNom->suivNom , listeApresRech );
	return ListeLNom;
}
	
//fonctions de sauvegarde du fichier lecteur

void sauvegardeLecteur(ListeLecteur listeLNum)

{
	FILE *flot;
	flot=fopen("lecteur.don","w");
	if (flot==NULL)
	{
		printf("Problème flot\n");
		fclose(flot);	
		exit(1);
	}
	while (listeLNum!=NULL)
	{
		printLecteur(listeLNum,flot);
		listeLNum=listeLNum->suivNum;
	}
	printf("\nFichier bien sauvegardé sous 'lecteur.don'\n"); 
	fclose(flot);
}



void printLecteur(ListeLecteur listeLNum,FILE *flot)

{
	fprintf(flot,"%s\n",listeLNum->l.numLecteur);
	fprintf(flot,"%s\n",listeLNum->l.nom);
	fprintf(flot,"%s\n",listeLNum->l.prenom);
	fprintf(flot,"%d\t",listeLNum->l.adresse.numRue);
	fprintf(flot,"%s\n",listeLNum->l.adresse.nomRue);
	fprintf(flot,"%s\n",listeLNum->l.adresse.ville);
	fprintf(flot,"%d\n",listeLNum->l.adresse.numDepartement);
}

//fonctions de modification d'une adresse pour un lecteur donné

ListeLecteur menuModifAdresse(ListeLecteur listeLNum)

{
	char NumLecRech[6],c;
	int trouve;
	ListeLecteur aux1,aux2;
	printf("\nDe quel lecteur voulez vous modifier l'adresse (Entrez son numéro de lecteur :)\n");
	scanf("%s",NumLecRech);
	aux1=rechercheNum(NumLecRech,&trouve,listeLNum,c);
	if (trouve==1)
	{
		listeLNum=modifAdresse(listeLNum,aux1);
		printf("\nLes modifications de l'adresse du client %s ont bien été effectuées !\n",NumLecRech);
	}
	return listeLNum;
}

ListeLecteur modifAdresse(ListeLecteur listeLNum,ListeLecteur listeApresRech)

{
	if(listeLNum==listeApresRech)
	{
		listeLNum->l.adresse=rentrerAdresse(listeLNum);
		return listeLNum;
	}
	listeLNum->suivNum=modifAdresse(listeLNum->suivNum , listeApresRech);
}

Adresse rentrerAdresse(ListeLecteur listeLNum)

{
	Adresse a;
	printf("Nouvelle ville :\n");
	fgets(a.ville,28,stdin);
	a.ville[strlen(a.ville)-1]='\0';

	printf("Nouveau numéro de domicile :\n");
	scanf("%d%*c",&a.numRue);

	printf("Nouveau nom de la rue :\n");
	fgets(a.nomRue,28,stdin);
	a.nomRue[strlen(a.nomRue)-1]='\0';

	printf("Nouveau numéro de département :\n");
	scanf("%d%*c",&a.numDepartement);
	return a;
}


//FONCTIONS POUR LES OUVRAGES


//fonctions de chargement du fichier ouvrage dans un tableau dynamique de pointeurs

Ouvrage **ChargementOuvrage(int *tmax,int *nb)

{
	Ouvrage **Touv,o,**aux;
	FILE *flot;
	flot=fopen("ouvrage.don","r");
	if (flot==NULL)
	{	
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	*nb=0;
	*tmax=5;	
	Touv=(Ouvrage **)malloc(*tmax*sizeof(Ouvrage *));
	if (Touv==NULL)
	{	
		printf("Problème malloc\n");
		fclose(flot);
		exit(1);
	}
	o=lireOuvrage(flot);
	while (!feof(flot))
	{
		if (*nb==*tmax)
		{
			*tmax=*tmax+5;
			aux=(Ouvrage **)realloc(Touv,*tmax*sizeof(Ouvrage *));
			if (aux==NULL)
			{
				printf("Problème malloc\n");
				fclose(flot);
				exit(1);
			}
			Touv=aux;
		}
		Touv[*nb]=(Ouvrage *)malloc(sizeof(Ouvrage));
		if (Touv[*nb]==NULL)
		{
			printf("Problème malloc\n");
			fclose(flot);
			exit(1);
		}
		*Touv[*nb]=o;
		*nb=*nb+1;
		o=lireOuvrage(flot);
	}
	fclose(flot);
	return Touv;
}	
	




Ouvrage lireOuvrage(FILE *flot)

{
	Ouvrage o;
	char Dispo[15];
	fscanf(flot,"%s\n",o.cote);

	fgets(o.titre,28,flot);
	o.titre[strlen(o.titre)-1]='\0';
	
	fgets(o.categorie,28,flot);
	o.categorie[strlen(o.categorie)-1]='\0';

	fscanf(flot,"%s",Dispo);
	if (strcmp(Dispo,"dispo")==0)
		o.dispo=vrai;
	else o.dispo=faux;
	return o;
}

//fonctions d'insertion d'un ouvrage

int rechercheDichotomie(Ouvrage **tab,int nb,char coteRech[])

{
	int inf,sup,m;
	inf=0;
	sup=nb-1;
	while (inf<=sup)
	{
		m=(inf+sup)/2;
		if (strcmp(coteRech,tab[m]->cote)==0)
			return -1;
		if (strcmp(coteRech,tab[m]->cote)>0)
			inf=m+1;
		else sup=m-1;
	}
	return inf;
}

Ouvrage **insererOuvrage(Ouvrage **Touv,int *nb,int *tmax)

{
	Ouvrage o,**aux;
	int posInsertion,choix;
	o=ajouterOuvrageAuClavier();
	posInsertion=rechercheDichotomie(Touv,*nb,o.cote);
	if (posInsertion==-1)
	{
		printf("\n--- ERREUR : UN OUVRAGE PORTE DEJA LA MEME COTE INSERTION IMPOSSIBLE ---\n");
		return Touv;
	}
	printf("\n%s\t%s\t%s",o.cote,o.titre,o.categorie);
	printf("\nEtes vous sûr de vouloir ajouter cet ouvrage ? (0=Oui/1=Non)\n");
	scanf("%d%*c",&choix);
	if (choix==1)
	{
		printf("\n--- INSERTION ANNULEE ---\n");
		return Touv;
	}
	if (*nb==*tmax)
	{
		*tmax=*tmax+5;
		aux=(Ouvrage **)realloc(Touv,*tmax*sizeof(Ouvrage *));
		if (aux==NULL)
		{
			printf("Problème malloc\n");
			exit(1);
		}
		Touv=aux;
	}
	Touv[*nb]=(Ouvrage *)malloc(sizeof(Ouvrage));
	if (Touv[*nb]==NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	Touv=decalerAdroite(Touv,posInsertion,*nb);
	*Touv[posInsertion]=o;
	*nb=*nb+1;
	printf("\n--- INSERTION CORRECTEMENT EFFECTUEE ---\n");
	return Touv;
}
	
	

Ouvrage **decalerAdroite(Ouvrage **Touv,int pos,int nb)

{
	for (nb;nb>pos;nb--)
		*Touv[nb]=*Touv[nb-1];
	return Touv;
}


Ouvrage ajouterOuvrageAuClavier(void)

{
	Ouvrage o;

	printf("Côte de l'ouvrage :\n");
	scanf("%s%*c",o.cote);

	printf("Titre de l'ouvrage :\n");
	fgets(o.titre,28,stdin);
	o.titre[strlen(o.titre)-1]='\0';
	
	printf("Catégorie de l'ouvrage :\n");
	fgets(o.categorie,28,stdin);
	o.categorie[strlen(o.categorie)-1]='\0';
	
	o.dispo=vrai;
	return o;
}



//fonctions d'affichage de la liste des livres de la bibliothèque

void afficherOuvrage(Ouvrage **Touv,int nb)

{
	int i;
	for (i=0;i<nb;i++)
		printf("%s\t\t%s\t\t%s\n",Touv[i]->cote,Touv[i]->titre,Touv[i]->categorie);
}


//fonctions de sauvegarde du fichier ouvrage

void sauvegardeOuvrage(Ouvrage **Touv,int nb)

{	
	int i=0;
	FILE *flot;
	flot=fopen("ouvrage.don","w");
	if (flot==NULL)
	{
		printf("Problème flot\n");
		fclose(flot);	
		exit(1);
	}
	while (i!=nb)
	{
		printOuvrage(Touv,flot,i);
		i=i+1;
	}
	printf("\nFichier bien sauvegardé sous 'ouvrage.don'\n"); 
	fclose(flot);
}



void printOuvrage(Ouvrage **Touv,FILE *flot,int i)

{
	fprintf(flot,"%s\n",Touv[i]->cote);
	fprintf(flot,"%s\n",Touv[i]->titre);
	fprintf(flot,"%s\n",Touv[i]->categorie);
	if (Touv[i]->dispo==vrai)
		fprintf(flot,"dispo\n");
	else fprintf(flot,"emprunte\n");
}


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
	flot=fopen("emprunt.don","r");
	if (flot==NULL)
	{
		printf("Problème flot\n");
		fclose(flot);
		exit(1);
	}
	emp=lireEmprunt(flot);
	listeLEmp=insererEmprunt(listeLEmp,emp);
	while(!feof(flot))
	{
		emp=lireEmprunt(flot);
		listeLEmp=insererEmprunt(listeLEmp,emp);
	}
	fclose(flot);
	return listeLEmp;
}

Emprunt lireEmprunt(FILE *flot)

{
	Emprunt emp;
	fscanf(flot,"%s%*c\n",emp.cote);
	fscanf(flot,"%s%*c\n",emp.numLecteur);

	fscanf(flot,"%d/%d/%d%*c\n",&emp.dateEmprunt.jour,&emp.dateEmprunt.mois,&emp.dateEmprunt.annee);
	return emp;
	
	
}

//fonctions d'insertion d'un emprunt

ListeEmprunt ajouterEnTeteEmprunt(ListeEmprunt listeLEmp,Emprunt emp)

{
	MaillonEmprunt *m;
	m=(MaillonEmprunt *)malloc(sizeof(MaillonEmprunt));
	if (m==NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	m->e=emp;
	m->suivEmprunt=listeLEmp;
	return m;
}

ListeEmprunt insererEmprunt(ListeEmprunt listeLEmp,Emprunt emp)

{
	if (listeLEmp==NULL)
			return ajouterEnTeteEmprunt(listeLEmp,emp);
	if (strcmp(emp.cote,listeLEmp->e.cote)<0)
			return ajouterEnTeteEmprunt(listeLEmp,emp);
	if (strcmp(emp.cote,listeLEmp->e.cote)==0)
		return listeLEmp;
	listeLEmp->suivEmprunt=insererEmprunt(listeLEmp->suivEmprunt,emp);
	return listeLEmp;
}

ListeEmprunt insererClavierEmprunt(ListeEmprunt listeLEmp ,Ouvrage **Touv , ListeLecteur listeLNum , int nbOuv)
{
	Emprunt emp ;
	int rangOuv , trouve;
	printf("Référence de l'emprunteur ?\n");
	scanf("%s%*c",emp.numLecteur);
	trouve=ExisteNumLec(listeLNum,emp.numLecteur);
	if(trouve==0)
	{
		printf("Lecteur introuvable");
		return listeLEmp;
	}
	printf("Cote de l'ouvrage ?\n");
	scanf("%s%*c",emp.cote);
	rangOuv=existeOuvrage(Touv , emp.cote , nbOuv );
	if(rangOuv==-1)
	{
		printf("ouvrage introuvable");
		return listeLEmp ;
	}
	if(Touv[rangOuv]->dispo==faux)
	{
		printf("Ouvrage indisponible désolé");
		return listeLEmp;
	}
	printf("Date de l'emprunt ? (jj/mm/yyyy)\n");
	scanf("%d/%d/%d%*c",&(emp.dateEmprunt.jour),&(emp.dateEmprunt.mois),&(emp.dateEmprunt.annee) );
	Touv[rangOuv]->dispo=faux;
	listeLEmp=insererEmprunt(listeLEmp,emp);
	

	return listeLEmp ;
}


//fonction d'affichage de la liste des emprunts en cours


void afficherEmprunt(ListeEmprunt listeL)
{
    printf("\n-----------------------------------------------------------------------------------------------------\n");
    printf("Cote\t\tLecteur\tdateEmprunt\n\n");
    while(listeL != NULL )
    {
    	printf("%s\t%s\t%d/%d/%d\n",listeL->e.cote,listeL->e.numLecteur,listeL->e.dateEmprunt.jour,listeL->e.dateEmprunt.mois,listeL->e.dateEmprunt.annee);
	listeL=listeL->suivEmprunt;
    }
    printf("-----------------------------------------------------------------------------------------------------\n");

}


//Recherche ouvrage

int existeOuvrage(Ouvrage **Touv , char cote[] ,int nbOuv)
{
	int i ;
	for(i=0;i<nbOuv;i++)
	{
		if(strcmp(cote,Touv[i]->cote)==0)
		{
		return i ;
		}
	}
	return -1;
}

//fonctions de sauvegarde du fichier emprunt

void sauvegardeEmprunt(ListeEmprunt listeLEmp)

{
	FILE *flot;
	flot=fopen("emprunt.don","w");
	if (flot==NULL)
	{
		printf("Problème flot\n");
		fclose(flot);	
		exit(1);
	}
	while (listeLEmp!=NULL)
	{
		printEmprunt(listeLEmp,flot);
		listeLEmp=listeLEmp->suivEmprunt;
	}
	printf("\nFichier bien sauvegardé sous 'emprunt.don'\n"); 
	fclose(flot);
}


void printEmprunt(ListeEmprunt listeLEmp,FILE *flot)

{
	fprintf(flot,"%s\n",listeLEmp->e.cote);
	fprintf(flot,"%s\n",listeLEmp->e.numLecteur);
	fprintf(flot,"%d/%d/%d\n",listeLEmp->e.dateEmprunt.jour,listeLEmp->e.dateEmprunt.mois,listeLEmp->e.dateEmprunt.annee);
}


//fonction date de retour

ListeEmprunt RetourEmprunt(ListeEmprunt listeLEmp ,Ouvrage **Touv , int nbOuv)
{
	ListeEmprunt aux;
	Date dateretour;
	int joursEmp , rangOuv;
	char cote[11],c;
	printf("Cote de l'ouvrage ?\n");
	scanf("%s%*c",cote);
	rangOuv=existeOuvrage(Touv , cote , nbOuv );
	if(rangOuv==-1)
	{
		printf("ouvrage introuvable");
		return listeLEmp ;
	}
	if(Touv[rangOuv]->dispo==vrai)
	{
		printf("Ouvrage déja disponible");
		return listeLEmp;
	}
	aux=trouverEmprunt(listeLEmp , cote);
	printf("Date de retour ? (jj/mm/yyyy)\n");
	scanf("%d/%d/%d%*c",&(dateretour.jour),&(dateretour.mois),&(dateretour.annee) );
	joursEmp=compareDate(listeLEmp->e.dateEmprunt,dateretour);
	while(joursEmp<0)
	{
		printf("Date incohérente !! Date de retour ? (jj/mm/yyyy)\n");
		scanf("%d/%d/%d%*c",&(dateretour.jour),&(dateretour.mois),&(dateretour.annee) );
		joursEmp=compareDate(listeLEmp->e.dateEmprunt,dateretour);
	}
	if(joursEmp > 15 )
		printf("Délais de 15 jours non respecté ! Le lecteur doit payer une amande !");
	c=getchar();
	return SuppEmp(listeLEmp,cote);
}



//fonction compare date

int compareDate(Date d1 , Date d2)
{
	int dateJ1,dateJ2,result;
	dateJ1=(d1.jour)+((d1.mois)*30)+((d1.annee)*365);
	dateJ2=(d2.jour)+((d2.mois)*30)+((d2.annee)*365);
	result=dateJ2-dateJ1;
	return result;
}



ListeEmprunt trouverEmprunt(ListeEmprunt listeLEmp , char cote[] )
{
	if(strcmp(cote,listeLEmp->e.cote)==0)
		return listeLEmp;
	return trouverEmprunt(listeLEmp->suivEmprunt , cote );
}


//supprimer en tete

ListeEmprunt Suppentete(ListeEmprunt listeLEmp )
{
	MaillonEmprunt *aux;
	if(listeLEmp==NULL)
		{
		printf("OP interdite");
		exit(1);
		}
	aux=listeLEmp;
	listeLEmp=listeLEmp->suivEmprunt;
	free(aux);
	return listeLEmp;
}

ListeEmprunt SuppEmp(ListeEmprunt listeLEmp, char cote[])
{
	if(listeLEmp==NULL)
		return listeLEmp;
	if(strcmp(cote,listeLEmp->e.cote)==0)
		return Suppentete(listeLEmp);
	listeLEmp->suivEmprunt=SuppEmp(listeLEmp->suivEmprunt,cote);
	return listeLEmp;
}

















