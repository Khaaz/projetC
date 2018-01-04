#include "projet.h"


// fonction Liste Lecteur

ListeLecteur listeVide (void)
{
    return NULL;
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
    if ( strcmp(m->l.numLecteur, listeL->l.numLecteur) == 0) {
        printf("Lecteur déja présent\n");
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
    if ( strcmp(m->l.nom, listeL->l.nom) == 0) {

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

void afficherLec(ListeLecteur listeL,int menu)
{
    while(listeL != NULL )
		{
    	printf("%s\t%s\t%s\t%d %s %s %d\n",listeL->l.numLecteur,listeL->l.nom, listeL->l.prenom, listeL->l.adresse.numRue, listeL->l.adresse.nomRue, listeL->l.adresse.ville, listeL->l.adresse.numDepartement);
		if (menu==4)
    		listeL=listeL->suivNom;
		else
			listeL=listeL->suivNum;
		}
	printf("\n");

}


ListeLecteur rechercheNum(char numLecteur[], int *trouve , ListeLecteur listeLNum , char c)
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
		

ListeLecteur supprimer1(ListeLecteur ListeLNum , ListeLecteur listeApresRech )
{
	if(ListeLNum==listeApresRech)
		{
		ListeLNum=NULL;
		printf("\n--- LECTEUR CORRECTEMENT SUPPRIMER ---\n");
		return ListeLNum;
		}
	if(ListeLNum->suivNum==listeApresRech)
		{
		ListeLNum->suivNum=listeApresRech->suivNum;
		printf("\n--- LECTEUR CORRECTEMENT SUPPRIMER ---\n");
		return ListeLNum;
		}
	return supprimer1(ListeLNum->suivNum , listeApresRech );
}

ListeLecteur supprimer2(ListeLecteur ListeLNom , ListeLecteur listeApresRech )
{
	if(ListeLNom==listeApresRech)
		{
		ListeLNom=NULL;
		return ListeLNom;
		}
	if(ListeLNom->suivNom==listeApresRech)
		{
		ListeLNom->suivNom=listeApresRech->suivNom;
		return ListeLNom;
		}
	return supprimer2(ListeLNom->suivNom , listeApresRech );
}
	



































