#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/*
 * NOM : PENA CAMPOS
 * PRENOM : Mateo
 */


// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
    if(argc<3 || argc>5) 
	{
		printf("Invalid Number Of Arguments\n");
		return 0;
	}

	if(strcmp(argv[1],"-s")==0) 
	{
		if(!symlink(argv[2],argv[3])) 
			printf("Soft link created\n");
		else
			perror("symlink"); 

	}
	else if(argc==3)
	{
		if(!link(argv[1],argv[2])) 
			printf("Hard link created\n");
		else
			perror("link"); 
	}

	else
		printf("Syntax Error\n"); 

        
	return EXIT_FAILURE;
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
