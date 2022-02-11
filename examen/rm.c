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
char buff[BUFSIZE];

void stop(char* message){
	perror(message);
	exit(EXIT_FAILURE);
}

void path(char* mypath){
	if((mypath = getcwd(buff, BUFSIZE))==NULL)
		stop("getcwd error");
}

// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
	char* mypath;
	mypath = getcwd(buff, BUFSIZE);
	printf("%s",mypath);
	if(unlink(mypath) < 0)
		stop("unlink error");
	
	return EXIT_SUCCESS;
}



// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
