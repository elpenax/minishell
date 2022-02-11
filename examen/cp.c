#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 4096

/*
 * NOM : PENA CAMPOS
 * PRENOM : Mateo
 */


// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
	if(argc < 2){}
else{
	int fdsrc, fddst;
	char buffer[BUFSIZE];
	int nchar;

	fdsrc = open(argv[1], O_RDONLY);
	fddst = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); 
	while((nchar = read(fdsrc,buffer,BUFSIZE))){
		write(fddst,buffer,nchar);
	}
	close(fdsrc);
	close(fddst);
}

return EXIT_SUCCESS;
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
