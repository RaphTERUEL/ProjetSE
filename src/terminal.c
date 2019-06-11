#include "headers/header.h"
#include <time.h>
char * saisircomande(char commande[100]){
	char taille[100];
	int size=0;
	size=read(0,commande,sizeof(taille));
	commande[size-1]='\0';
	return commande ;
}
void CommandeArguments(char commande[],char* argv[],int * argc ){
	char * argument;

	argument=strtok(commande," ");

	while(argument!= NULL && *argc<10){
		argv[*argc]=argument;
		argument=strtok(NULL," ");
		*argc=*argc+1;
	}

}

int Interpreteur(char* argv[],int argc,disk * mondisk){

	if (!strcmp(argv[0],"exit")&& argc==1)
	{
		return 0;
		mondisk->inode->nb_inode++;
	}
	if (!strcmp(argv[0], "mkdir"))
	{

		if(argc > 1)
		{
			for (int i = 1; i < argc; ++i)
			{
				mymkdir(argv[i],mondisk);
			}
			
		}
		return 1;
	}
	else if(!strcmp(argv[0], "ls"))
	{

		if(argc ==1)
		{
			myls(mondisk);			
		}	
		return 1;
	}
	return 1;
}


void terminal(disk *mondisk){
	int exite=1;

	while(exite)
	{
		write(0,"user@pc-user:$ ",16);
		char entrer[100];
		int argc=0;
		char* argv[10];
		saisircomande(entrer);
		CommandeArguments(entrer,argv,&argc);
		exite=Interpreteur(argv,argc,mondisk);	
	}
	printf("%d",exite);
	

}