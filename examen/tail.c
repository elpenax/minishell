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



void printLine(FILE *file, int startline)
{
	int fd;
	fd= fileno(file);
	int count;
	char buffer[100];
	lseek(fd,(startline + 1),SEEK_SET); 
	while((count= read(fd,buffer,sizeof(buffer))) > 0) 
	{
		write(1, buffer, count);
	}
}

void scanFile(int n, FILE *filename)
{
	int fposition;
	int index;
	int end;
	long countlines= 0;
	char cbyte;
	
	fseek(filename,0,SEEK_END); 
	fposition= ftell(filename); 
	index= fposition;
	end= fposition;
	for(index; index >= 0; index --) 
	{
		cbyte= fgetc(filename);
		if (cbyte == '\n' && (end - index) > 1) 
		{
			countlines ++; 
			if(countlines == n) 
			{
				break;
			}
		}
		fposition--;
		fseek(filename,fposition,SEEK_SET); 
	}
	printLine(filename, fposition); 
	fclose(filename); 
}



// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
	int n, i;
	FILE *file;

	if(argc<2)
	{
		printf("Invalid number of arguments\n");
		return EXIT_FAILURE;
	}
	
	n=(int) strtol(argv[1],(char **)0,10); 
	
	if(n)
	{	
		for(i=2;i<argc;i++)
		{
			file= fopen(argv[i], "r"); 
			if(file == NULL)
			{	
	  			perror("fopen");
			}
			scanFile(abs(n),file); 
		}
	}
	else 
	{
		for(i=1;i<argc;i++)
		{
			file= fopen(argv[i], "r"); 
			if(file == NULL)
			{	
	  			perror("fopen");
			}
			scanFile(10,file);
		}
	}	

	return EXIT_FAILURE;
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
