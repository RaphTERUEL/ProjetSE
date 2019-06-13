#include "headers/header.h"


int mymkdir(char *nom, disk *mondisk)
{//primitive pour créer un dossier

   	creeinode(mondisk);
   	creerepertoir(mondisk->inode->nb_inode-1,nom, mondisk);

   return 0;
}

int mytouch(char* nom, disk* mondisk){//primitive pour créer un fichier texte

	creeinode(mondisk);
	creefichier(mondisk->inode->nb_inode-1, nom, mondisk);

	return mondisk->inode->nb_inode-1;
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

void mywrite(int inode, char* buffer, int nombre, disk *mondisk){
	if(inode > 0){
		char message[nombre+1];
		strncpy(message, buffer, nombre);
		add_data_to_inode(mondisk, inode, message);
	}
}

void myread(int inode, char* buffer, int nombre, disk* mondisk){
	if(inode > 0){
		infoinode* i = NULL;
		i = get_inode(inode, mondisk);
        char mess[(i->taille)+1];
        mess[0] = 0;
        int len = 0;
		if(i->typefichier == 1){
			int b = 0;
			infobloc* bloc = NULL;
			for(b=0;b<nb_blocutiliser(i->blocutiliser);b++){
                int pos=0;
				bloc = &mondisk->bloc[i->blocutiliser[b]];
				if(nombre < bloc->taille){
                    for(pos=0;pos<nombre;pos++)
                    {
                        mess[len] = bloc->unbloc[pos];
                        len++;
                    }
				}else{
					for(pos=0;pos<bloc->taille;pos++)
                    {
                        mess[len] = bloc->unbloc[pos];
                        len++;
                    }
                    nombre-=bloc->taille;
				}
			}
			mess[len] = 0;
            strcpy(buffer, mess);
		}
	}
}

int nom_to_inode(char* nom, disk* mondisk){
	infoinode* i = get_inode(courant, mondisk);
	int blocutil=nb_blocutiliser(i->blocutiliser);
	for (int j = 0; j < blocutil; j++)
	{
		infobloc*b = &mondisk->bloc[i->blocutiliser[j]];
		for (int i = 0; i < b->taille; i++)
        {
            char nomlu[11] = {0};
            char numlu[3] = {0};
		    while (b->unbloc[i] != ' ')
		    {//affiche les données de chaque ligne du bloc jusqu'à l'espace
                nomlu[strlen(nomlu)] = b->unbloc[i];
                i++;
		    }
		    i++;
		    nomlu[strlen(nomlu)] = '\0';
		    while (b->unbloc[i] != '\n')
            {
                numlu[strlen(numlu)] = b->unbloc[i];
                i++;
            }
            numlu[strlen(numlu)] = 0;
		    if(!strcmp(nomlu, nom))
                return atoi(numlu);
        }
	}
	return -1;
}

void mycat(int inode, disk* mondisk){
	if(inode > 0){
		char message[30*1024] = {0};
		myread(inode, message, 30*1024, mondisk);
		printf("%s\n",message);
	}
}

void mycd(char *nom, disk *mondisk){
	int i=myopen(nom,mondisk);
	if(i!=-1){
		
		infoinode * inode=get_inode(i,mondisk);
		if(inode->typefichier==3){
			courant=i;
			
		}
		else
			printf("ce n'est pas un dossier\n");
	}
	else
		printf("ce dossier n'existe pas\n");

}

int myopen(char *nom, disk *mondisk){
	char * numinod=NULL;
	int j=0;
	infoinode* i;
	i=get_inode(courant,mondisk);
	
	
	
	while(i->blocutiliser[j]!=-1)
	{
		char data[1024] = { 0 };
		strcpy(data, mondisk->bloc[i->blocutiliser[j]].unbloc);
	
		numinod=strstr(data,nom);

		if(numinod!= NULL){
			numinod=strtok(numinod,"\n");
			numinod=strtok(numinod," ");
			numinod=strtok(NULL," ");
			
			return atoi(numinod);			
		}
		j++;
	}
	return -1;
}

