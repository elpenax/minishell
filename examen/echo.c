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


#define BUFSIZE 255

// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
	int i;
	for(i=1; i<argc; i++){
		if(i==argc-1)
			printf("%s\n",argv[i]);
		else
    			printf("%s ",argv[i]);
	}

    	exit(EXIT_SUCCESS);
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
