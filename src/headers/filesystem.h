#ifndef FILESYSTEM_H
# define FILESYSTEM_H



typedef struct infoinode
{
  char permissions[9];
  int blocutiliser[30]; 
  int typefichier;        
  int taille;
  struct infoinode *next;  
}infoinode;

typedef struct
{
  infoinode *first; 
  int nb_inode;  
}inodelist;

typedef struct 
{

  char unbloc[1024]; 
  int taille;      //nombre de char du bloc
}infobloc;

typedef struct
{
  inodelist * inode;
  infobloc bloc[60]; 
}disk;



void init(disk *mondisk);
void creeinode(disk *mondisk);
infoinode *get_inode(int numinode, disk *mondisk);
infoinode *recupe_inode_from_num(int numinode, disk *mondisk);
void creerepertoir(int nouvelinode, char *nom, disk *mondisk);
int get_free_bloc(disk *mondisk);
int nb_blocutiliser(int blocutiliser[]);
void root(disk *mondisk);
void add_data_to_inode(disk *mondisk, int inode, char *data);
void add_bloc_to_inode(int blocnum, infoinode *inode);
char *add_data_to_bloc(disk *mondisk, int numbloc, char *data);


#endif 
