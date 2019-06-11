#include "headers/header.h"


int mymkdir(char *nom, disk *mondisk)
{//primitive pour créer un dossier
 
   	creeinode(mondisk);
   	creerepertoir(mondisk->inode->nb_inode-1,nom, mondisk);
  
   return 0;
}


void myls(disk *mondisk)
{//primitive ls
  infoinode *i = get_inode(courant, mondisk);
  int blocutil=nb_blocutiliser(i->blocutiliser);
  for (int j = 0; j < blocutil; j++)
  {
  			
	  infobloc*b = &mondisk->bloc[i->blocutiliser[j]];
	  for (int i = 0; i < b->taille; i++)
	  {
		    while (b->unbloc[i] != ' ')
		    {//affiche les données de chaque ligne du bloc jusqu'à l'espace
		      printf("%c", b->unbloc[i]);
		      i++;
		    }
		    while (b->unbloc[i] != '\n')
		      i++;
		    printf(" ");
	  }
	}
  printf("\n");
}
