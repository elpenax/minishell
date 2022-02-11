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


void stop(char *message){
	perror(message);
	exit(EXIT_FAILURE);
	
}

// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
int fd;
if((fd = open(argv[1], O_CREAT, 00700)) < 0)
	stop("open error");
return EXIT_SUCCESS;
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
