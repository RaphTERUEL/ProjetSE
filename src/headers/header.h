#ifndef HEADER_H
# define HEADER_H
# define _GNU_SOURCE // fonctions getline et strdup, pour le fichier
                     // filesystem.c
int courant;

// HEADER PRINCIPAL, INCLU DANS TOUS LES FICHIERS .c

// bibliothèques:
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>


// nos autres headers
# include "filesystem.h"
# include "terminal.h"
# include "primitives.h"
#endif
