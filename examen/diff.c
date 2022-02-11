#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/*
 * NOM : PENA CAMPOS
 * PRENOM : Mateo
 */


// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
    FILE *file1, *file2;
    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");

    if((file1==NULL) || (file2==NULL)){
        perror("file error");
        exit(errno);
    }

    char ch1, ch2;
    ch1 = getc(file1);
    ch2 = getc(file2);
 
    while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
        ch1 = getc(file1);
        ch2 = getc(file2);
    }
 
    if (ch1 == ch2)
    printf("OK \n");
    else if (ch1 != ch2)
    printf("DIFFERENT \n");
 
    fclose(file1);
    fclose(file2);
	return EXIT_FAILURE;
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
