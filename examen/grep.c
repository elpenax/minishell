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
#define BUFSIZE 20

void stop(char *message){
	perror(message);
	exit(EXIT_FAILURE);
	
}

// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
char buffer[BUFSIZE];
	int file;
	if((file = open(argv[2], O_RDWR, 00700)) < 0)
		stop("open error");
	if(read(file, buffer, BUFSIZE) < 0)
			stop("read error");
		if(strstr(buffer, argv[1] ) != NULL)
			printf("PRESENT\n");
	return EXIT_SUCCESS;

}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
