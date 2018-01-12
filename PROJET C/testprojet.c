#include "projet.h"

void test (void)
{
    ListeLecteur listeLNom , listeLNum;
    ListeEmprunt listeLEmp;
    Ouvrage **Touv;
	listeLNom = listeVide();
	listeLNum = listeVide();
	listeLEmp = listeVideE();
	int menu , choixM , tmaxOuvrage, nbOuvrage;
	char c;
	system("clear");
	listeLNum=ChargementLecteur(listeLNum,&listeLNom);
	printf("Fichier lecteur chargé\n");
	Touv=ChargementOuvrage(&tmaxOuvrage,&nbOuvrage);
	printf("Fichier ouvrage chargé\n");
	listeLEmp=ChargementEmprunt(listeLEmp);
	printf("Fichier emprunt chargé\n");
	choixM=MenuPRINCIPAL();
	while(choixM!=0)
	{
		if (choixM==1)
		{
			system("clear");
			menu=MenuLecteur();
			while (menu!=0)
			{
				switch(menu)
				{
					case 1 : system("clear");listeLNum=ajouterLecteurAuClavier(listeLNum,&listeLNom);break;
					case 2 : system("clear");system("clear");listeLNum=SupprimerGENERAL(listeLNum,&listeLNom);break;
					case 3 : system("clear");AffichInfosLec(listeLNum);break;
					case 4 : system("clear");afficherLec(listeLNom,menu) ;break;
					case 5 : system("clear");afficherLec(listeLNum,menu) ;break;
					case 6 : system("clear");sauvegardeLecteur(listeLNum);break;
					case 7 : system("clear");listeLNum=menuModifAdresse(listeLNum);break;
				}
				printf("\n--- APPUYEZ SUR ENTRER POUR REVENIR AU MENU LECTEUR ---");
				c=getchar();
				system("clear");
				menu=MenuLecteur();
			}
		}
		if (choixM==2)
		{
			system("clear");
			menu=MenuOuvrage();
			while (menu!=0)
			{
				switch(menu)
				{
					case 1 : system("clear");Touv=insererOuvrage(Touv,&nbOuvrage,&tmaxOuvrage);break;
					case 2 : system("clear");afficherOuvrage(Touv,nbOuvrage);break;
					case 3 : system("clear");sauvegardeOuvrage(Touv,nbOuvrage);break;
				}
				printf("\n--- APPUYEZ SUR ENTRER POUR REVENIR AU MENU OUVRAGE ---");
				c=getchar();
				system("clear");
				menu=MenuOuvrage();
			}
		}
		if (choixM==3)
		{
			system("clear");
			menu=MenuEmprunt();
			while (menu!=0)
			{
				switch(menu)
				{
					case 1 : system("clear");listeLEmp=insererClavierEmpreint(listeLEmp,Touv,listeLNum,nbOuvrage);break;
					case 2 : system("clear");afficherEmprunt(listeLEmp);break;
					case 3 : system("clear");break;
					case 4 : system("clear");break;
				}
				printf("\n--- APPUYEZ SUR ENTRER POUR REVENIR AU MENU EMPRUNT ---");
				c=getchar();
				system("clear");
				menu=MenuEmprunt();
			}
		}
		system("clear");
		choixM=MenuPRINCIPAL();

	}
	system("clear");

}


int main(void)
{
    test();
    return 0;
}
