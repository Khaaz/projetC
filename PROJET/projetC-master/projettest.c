#include "projet.h"

void test (void)
{
    ListeLecteur listeLNom , listeLNum , aux1 ,aux2 ;
    Lecteur Lec;
	listeLNom = listeVide();
	listeLNum = listeVide();
	int menu , auxLNom , trouve;
	char c , NumLecRech[6] ;
	printf("\n1) Inserer nouveau lecteur\n2) Supprimer lecteur\n3) Afficher les information d'un lecteur \n4) Affichage des lecteurs par ordre alphabétique\n5) Affichage des lecteurs selon leur identifiant de lecteurs\n0)QUITTER\n\n--- Que voulez-vous faire ? ---\n");
	scanf("%d%*c",&menu);
	while(menu!=0)
		{
		switch(menu)
			{
			case 1 : printf("Nom ?\n");
					 fgets(Lec.nom,28,stdin);
					 Lec.nom[strlen(Lec.nom)-1]='\0';

					 printf("Prenom ?\n");
					 fgets(Lec.prenom,28,stdin);
					 Lec.prenom[strlen(Lec.prenom)-1]='\0';

					 printf("numero departement ?\n");
					 scanf("%d%*c",&(Lec.adresse.numDepartement));

					 printf("Ville ?\n");
					 fgets(Lec.adresse.ville,28,stdin);
					 Lec.adresse.ville[strlen(Lec.adresse.ville)-1]='\0';

					 printf("Nom de la rue ?\n");
					 fgets(Lec.adresse.ville,28,stdin);
					 Lec.adresse.nomRue[strlen(Lec.adresse.nomRue)-1]='\0';

					 printf("Numero du domicile ?\n");
					 scanf("%d",&(Lec.adresse.numRue));

					 printf("Numero de Lecteur ?\n");
					 scanf("%s",Lec.numLecteur);

					 printf("\n--- RESUME ---\n");
					 
					 printf("%s\t%s\t%s\t%d %s %s %d\n",Lec.numLecteur,Lec.nom, Lec.prenom,Lec.adresse.numRue, Lec.adresse.nomRue, Lec.adresse.ville, Lec.adresse.numDepartement);

					 printf("Voulez vous entrer ce lecteur ? (0=Oui 1=Non) \n");
					 scanf("%d%*c",&menu);
					 if (menu==0)
						{
					 	listeLNum = insererLec(listeLNum, &listeLNom , Lec );
						printf("\n--- LECTEUR ENREGISTRE ---\n");
						}

					 break;

			case 2 : printf("\n\tNumero de Lecteur ?\n");
					 scanf("%s",NumLecRech);
					 aux1=rechercheNum(NumLecRech,&trouve,listeLNum,c) ;
					 aux2=rechercheNom(NumLecRech,listeLNom);
					 if(trouve==1)
						{
					 	listeLNum = supprimer1(listeLNum , aux1 );
					 	listeLNom = supprimer2(listeLNom , aux2 );
					 	free(aux1);
						}
					 break;


			case 3 : printf("Numero de Lecteur ?\n");
					 scanf("%s",NumLecRech);
					 aux1=rechercheNum(NumLecRech,&trouve,listeLNum,c) ;
					 break;

			case 4 : afficherLec(listeLNom,menu) ;break;
			case 5 : afficherLec(listeLNum,menu) ;break;
			}
		c=getchar();
		system("clear");
		printf("\n1) Inserer nouveau lecteur\n2) Supprimer lecteur\n3) Afficher les information d'un lecteur\n4) Affichage des lecteurs par ordre alphabétique\n5) Affichage des lecteurs selon leur identifiant de lecteurs\n0)QUITTER\n\n--- Que voulez-vous faire ? ---");
		scanf("%d%*c",&menu);

		}

}


int main(void)
{
    test();
    return 0;
}
