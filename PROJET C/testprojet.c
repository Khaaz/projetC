#include "projet.h"

void test (void)
{
    ListeLecteur listeLNom , listeLNum , aux1 ,aux2 ;
    Lecteur Lec;
	listeLNom = listeVide();
	listeLNum = listeVide();
	int menu , auxLNom , trouve;
	char c , NumLecRech[6] ;
	listeLNum=ChargementLecteur(listeLNum,&listeLNom);
	printf("\nFichier lecteur chargé\n");
	menu=Menu();
	while(menu!=0)
		{
		switch(menu)
			{
			case 1 : system("clear");listeLNum=ajouterLecteurAuClavier(Lec,listeLNum,&listeLNom);break;
			case 2 : system("clear");system("clear");listeLNum=SupprimerGENERAL(listeLNum,&listeLNom);break;
			case 3 : system("clear");system("clear");AffichInfosLec(listeLNum);break;
			case 4 : system("clear");afficherLec(listeLNom,menu) ;break;
			case 5 : system("clear");afficherLec(listeLNum,menu) ;break;
			case 6 : system("clear");sauvegardeLecteur(listeLNum);break;
			case 7 : system("clear");listeLNum=menuModifAdresse(listeLNum);break;
			}
		printf("\n--- APPUYEZ SUR ENTRER POUR REVENIR AU MENU ---");
		c=getchar();
		system("clear");
		menu=Menu();

		}

}


int main(void)
{
    test();
    return 0;
}
