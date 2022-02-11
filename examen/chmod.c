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
int mpenacam(int argc, char** argv){
    int droit;
    sscanf(argv[1],"%d", &droit);
    const char* file_name = argv[2];
    int ch;
	if (droit<8){
		if((ch = chmod(file_name,droit))<0){
			perror("chmod < 8 ");
			exit(EXIT_FAILURE);
		}
	}
	else if(droit < 78){
		int dizaine = (int) (droit/10);
		int t = dizaine*8 + (droit-dizaine*10);
		if((ch = chmod(file_name, t))<0){
			perror("chmod < 78 ");
			exit(EXIT_FAILURE);
		}
	}
	else if(droit<778){
		int centaine = (int) (droit/100);
		int dizaine = (int) (droit/10) - centaine*10;
		int t = centaine*64 + dizaine*8 + (droit-(dizaine*10)-(centaine*100));
		if((ch = chmod(file_name, t))<0){
			perror(" chmod < 778 ");
			exit(EXIT_FAILURE);
		}
	}
	else{
		printf("Argument trop grand \n");
		exit(EXIT_FAILURE);
	}
	return EXIT_FAILURE;
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
