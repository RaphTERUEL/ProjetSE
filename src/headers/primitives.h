#ifndef PRIMITIVES_H
# define PRIMITIVES_H


int mymkdir(char *nom, disk *mondisk);
int mytouch(char* nom, disk* mondisk);
void myls(disk *mondisk);
void mywrite(int inode, char* buffer, int nombre, disk *mondisk);
void myread(int inode, char* buffer, int nombre, disk* mondisk);
int nom_to_inode(char* nom, disk* mondisk);
void mycat(int inode, disk* mondisk);
int myopen(char *nom, disk *mondisk);
void mycd(char *nom, disk *mondisk);

#endif
