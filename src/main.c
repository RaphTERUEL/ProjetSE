#include "headers/header.h"

int main()
{
 	
    disk mondisk;
   	root(&mondisk);
 	
   	mymkdir("lol",&mondisk);
 	mymkdir("chat",&mondisk);
 	
 	
	myls(&mondisk);
   		
   // myshell(disk);

    return 0;
}
