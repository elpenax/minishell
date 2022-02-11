#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

/*
 * NOM : PENA CAMPOS
 * PRENOM : Mateo
 */

static int nb_dir=0; //variable static utilisee pour ne pas ouvrir tous les sous-dossiers lors de l'appel recursif de print_stat

void print_stat(const char *ref, struct stat *statut) {
    
    struct passwd *pw;
    struct group *gr;
    char type;
    #define LTEMPS 32
    char pws[9], grs[9], temps[LTEMPS], *linked_file=malloc(32*sizeof(char));
    type = '?';
    
    if      (S_ISREG(statut->st_mode))  type = '-';
    else if (S_ISCHR(statut->st_mode))  type = 'c';
    else if (S_ISBLK(statut->st_mode))  type = 'b';
    else if (S_ISFIFO(statut->st_mode)) type = 'p';
    else if (S_ISLNK(statut->st_mode))  {						//Exercice 8
											char name[64]; 
											ssize_t len = readlink(ref, name, sizeof(name)-1);
											if (len == -1) 
												perror("error reading linked file");
											name[len] = '\0'; //readlink n'ajoute pas '\0'
											strcpy(linked_file, "-> ");
											strcat(linked_file,name);
											type = 'l';			
										}
    else if (S_ISDIR(statut->st_mode))  {						//Exercice 10
											if (nb_dir != 1){
												nb_dir++;
												DIR *dir;
												struct dirent *dp;
												if((chdir(ref) == -1))
													perror("could'nt change directory");
												if ((dir = opendir("."))==NULL){
													perror("couldn't open '.'"); return ;
												}
												while ((dp=readdir(dir))){
													if(strcmp(dp->d_name,".") && strcmp(dp->d_name,"..")){
														if (lstat(dp->d_name,statut) == -1) {
															fprintf(stderr, "impossible d'obtenir le statut de %s\n",dp->d_name);
															continue; 
														}
														print_stat(dp->d_name,statut);
													}
												}
												if(errno != 0) perror("error reading directory");
												closedir(dir);
												return;	
											}
											type = 'd';
										}

	if(!(type=='l'))
		linked_file = " ";

    strftime(temps, LTEMPS,"%a %e %h %Y %H:%M:%S", localtime(&(statut->st_mtime)));
    
    pw = getpwuid(statut->st_uid);
    
    if (pw != NULL) 
        strcpy(pws, pw->pw_name);
    else 
        sprintf(pws,"%8d", (int)statut->st_uid);
    
    gr = getgrgid(statut->st_gid);
    
    if (gr != NULL) 
        strcpy(grs, gr->gr_name);
    else 
        sprintf(grs, "%8d", (int)statut->st_gid);
    
    printf("%c%c%c%c%c%c%c%c%c%c %2d %8s %8s %9d %s %s %s\n", type,
    statut->st_mode&S_IRUSR ?'r':'-',
    statut->st_mode&S_IWUSR ?'w':'-',
    statut->st_mode&S_IXUSR ?'x':'-',
    statut->st_mode&S_IRGRP ?'r':'-',
    statut->st_mode&S_IWGRP ?'w':'-',
    statut->st_mode&S_IXGRP ?'x':'-',
    statut->st_mode&S_IROTH ?'r':'-',
    statut->st_mode&S_IWOTH ?'w':'-',
    statut->st_mode&S_IXOTH ?'x':'-',
    (int)statut->st_nlink, pws, grs, (int)statut->st_size, temps, ref, linked_file );
}


// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char* argv[])
{
	struct stat statut;
    int i;
    if (argc < 2) {
        if (fstat(STDIN_FILENO,&statut) == -1) {
            fprintf(stderr, "%s: impossible d'obtenir le statut de %s\n", argv[0], "<STDIN>");
            exit(EXIT_FAILURE);
        }
		if(lstat(".",&statut)==-1)
			fprintf(stderr, "%s: impossible d'obtenir le statut de %s\n", argv[0], argv[i]);
        print_stat(".", &statut);
    }
    else {
        for (i = 1; i<argc; i++) {
            if (lstat(argv[i], &statut) == -1) {
                fprintf(stderr, "%s: impossible d'obtenir le statut de %s\n", argv[0], argv[i]);
                continue; 
            }
            print_stat(argv[i], &statut); 
            
        }
    }
    exit(EXIT_SUCCESS);
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
