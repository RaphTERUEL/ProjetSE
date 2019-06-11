#ifndef TERMINAL_H
# define TERMINAL_H 

char* saisircomande();
void CommandeArguments(char commande[],char* argv[],int * argc  );
int Interpreteur(char* argv[],int argc,disk * mondisk);
void terminal(disk * mondisk);

#endif
