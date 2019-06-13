#include "header.h"



void init(disk *mondisk)
{

  mondisk->inode=malloc(sizeof(inodelist));
  mondisk->inode->first = NULL;
  mondisk->inode->nb_inode=0;
  courant=0;
}
void root(disk *mondisk)
{
  //init du répertoire root:
  init(mondisk);
  creeinode(mondisk);
  infoinode *root = get_inode(0, mondisk);
  root->typefichier = 3;
  root->taille = 0;
  char *data = ".. 0\n. 0\n";
  add_data_to_inode(mondisk, 0, data);
}


void creeinode(disk *mondisk)
{

  infoinode *new = malloc(sizeof(infoinode));
  infoinode *last =  mondisk->inode->first;
  new->next = NULL;
  new->taille = 0;
  new->typefichier = 0;
  int i;
  for (i = 0; i < 9; ++i)
    {
      new->permissions[i]=1;
    }
  for(i=0;i<30;i++){
    new->blocutiliser[i]=-1;
  }

  if (mondisk->inode->nb_inode==0)
  {
    mondisk->inode->first = new;
    mondisk->inode->nb_inode =1;

    return;
  }

  while (last->next != NULL)
    last = last->next;
  last->next = new;
  mondisk->inode->nb_inode ++;

}

infoinode *get_inode(int numinode, disk *mondisk)
{
  int i;
  if (numinode == 0)
    return mondisk->inode->first;
  if (numinode > mondisk->inode->nb_inode)
  {
    printf("inode demander inexistante\n");
    return NULL;
  }

  infoinode *inode = mondisk->inode->first;
  for (i = 0; i < numinode; i++)
     inode = inode->next;

  return inode;

}

void creerepertoir(int nouvelinode, char *nom, disk *mondisk)
{

  infoinode * new = get_inode(nouvelinode, mondisk);
  new->typefichier= 3;
  new->taille = 0;

  //ajoute les infos dans le bloc du dossier que l'on a créé
  char data[256] = { 0 };
  sprintf(data, ".. %d\n. %d\n", courant, nouvelinode);

  add_data_to_inode(mondisk, nouvelinode, data);

  //ajoute ses infos dans le bloc du dossier PWD
  char o_data[256] = { 0 };
  sprintf(o_data, "%s %d\n", nom,nouvelinode);
  add_data_to_inode(mondisk, courant, o_data);
}

void creefichier(int nouvelinode, char* nom, disk* mondisk){

	infoinode* new = get_inode(nouvelinode, mondisk);
	new->typefichier = 1;
	new->taille = 0;

	//ajoute ses infos dans le bloc du dossier PWD
	char o_data[256] = { 0 };
	sprintf(o_data, "%s %d\n", nom,nouvelinode);
	add_data_to_inode(mondisk, courant, o_data);
}

void add_data_to_inode(disk *mondisk, int inode, char *data)
{//ajoute les caractèes data à l'inode
  if (inode > mondisk->inode->nb_inode)
  {
    printf("inode inexistante\n");
  }
  infoinode *i = NULL;
  char *rest_of_data;
  int lastbloc;

  if ((i = get_inode(inode, mondisk)) != NULL)
  {

    if (nb_blocutiliser(i->blocutiliser)==0)
    {

      int bloc = get_free_bloc(mondisk);
      add_bloc_to_inode(bloc, i);
      lastbloc = bloc;
    }
    else
    {

      //récupère le dernier bloc de l'inode:
      for (int j = 0; j < 30; j++)
      {
        if(mondisk->bloc[i->blocutiliser[j]].taille<1024){
          lastbloc=i->blocutiliser[j];
          break;
        }
      }
      ////
    }

    //boucle sur tant qu'on n'a pas fini d'ajouter data a l'inode,
    //on ajoute un bloc, et on le remplit
    rest_of_data = data;
    while (rest_of_data != NULL)
    {
      rest_of_data = add_data_to_bloc(mondisk, lastbloc, rest_of_data);
      if (rest_of_data != NULL)
      {
        int new_bloc = get_free_bloc(mondisk);
        add_bloc_to_inode(new_bloc, i);
      }
    }
    i->taille += strlen(data);

  }
  else
  {
    printf("  System error: Could not write to inode %d\n", inode);
  }
}


void add_bloc_to_inode(int blocnum, infoinode *inode)
{//ajoute le bloc au blocs untilisés de l'inode
  int i=0;
  for (i = 0; i < 30 ; ++i)
  {
      if(inode->blocutiliser[i]==-1){
        inode->blocutiliser[i]=blocnum;
        return ;
      }
  }
}


int get_free_bloc(disk *mondisk)
{
  int i=0;
  for (i = 0; i < 60 ; ++i)
  {
      if(mondisk->bloc[i].taille==0){
        return i;
      }

  }
  printf("disk plein\n");
  return -1;
}

int nb_blocutiliser(int blocutiliser[]){
  int i=0;
  for (int i = 0; i < 30; ++i)
  {
    if(blocutiliser[i]==-1){
      return i;
    }
  }
  return i;
}


char *add_data_to_bloc(disk *mondisk, int numbloc, char *data)
{//ajoute les données data au bloc. Si data est trop grand, renvoie
 //ce qui n'a pas pu etre écrit
  infobloc *b = NULL;

  //verifie si le bloc est valide
  if (numbloc < 60)
  {
    b = &mondisk->bloc[numbloc];
    size_t available_space = 1024 - strlen(b->unbloc);
    if (strlen(data) <= available_space)
    {//si on peut écrire tout data dans le bloc
      strcat(b->unbloc, data);
      b->taille = strlen(b->unbloc);
      b->unbloc[b->taille] = '\0';
      return NULL;
    }
    else
    {
      //écrit les caractères que l'on peut
      char data_to_add[available_space];
      strncpy(data_to_add, data, available_space);
      data_to_add[available_space] = '\0';
      strcat(b->unbloc, data_to_add);

      //récupère les caractères restant
      int remaining_chars = strlen(data) - available_space;
      data = strdup(data + available_space);
      data[remaining_chars] = '\0';
      b->taille = 1024;
      b->unbloc[b->taille] = '\0';
      return data;
    }
  }
  else
  {

    return NULL;
  }
}




