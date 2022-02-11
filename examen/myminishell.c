#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>

#define BUFSIZE 512
#define PATH_MAX 256

//ma fonction pwd
int mypwd()
{
	char buffer[100];
	if(getcwd(buffer,sizeof(buffer)))
		printf("%s\n",buffer);
	else{
		perror("getcwd error");
        return EXIT_FAILURE;
    }

	return 0;
}

//ma fonction cd
int mycd(int args,char * path){
	if (args != 2)
        return EXIT_FAILURE;
    if (chdir(path) == 0)
        return 0;
    else
        perror("chdir error\n");
    return EXIT_FAILURE;
}



// passer a 1 pour obtenir des informations de DEBUG
int DEBUG = 0;

int read_command(char *command, char *arg[], char *fdest, int *flag)
{

    int cpta = 1;
    int c;
    char *chaine;
    char pwd[PATH_MAX];

    bzero(arg, BUFSIZE);
    bzero(command, BUFSIZE);
    
    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        perror("Displaying print working directory error");
        return 1;
    }

    scanf("%s", command);
    if (strcmp(command, "exit") == 0)
        return -1;


    while ((c = getchar()) != '\n')
    {
        chaine = malloc((BUFSIZE - 1) * sizeof(char));
        scanf("%s", chaine);
        if (!strcmp(chaine, ">"))
        {   
            *flag = 1 ;
            scanf("%s", fdest);
            break;
        }
        else if(!strcmp(chaine, ">>"))
        {
            *flag = 2;
            scanf("%s", fdest);
            break;
        }
        else if(!strcmp(chaine, "2>"))
        {
            *flag = 3;
            scanf("%s", fdest);
            break;
        }
        else if(!strcmp(chaine, "2>>"))
        {
            *flag = 4;
            scanf("%s", fdest);
            break;
        }
        else if(!strcmp(chaine, "&"))
        {
            *flag = 5;
            break;
        }
        arg[cpta++] = chaine;
    }
    return cpta;
}

int run_command(char *command,char *arg[],char *fdest, int flag)
{
    pid_t status;
    int fd;
    status=fork();
    switch(status)
    {
        case -1:
            perror("Creation processus");
            exit(EXIT_FAILURE);
        case 0:
            if(strlen(fdest) > 0)
            {
                switch (flag)
                {
                case 1 :
                    fd = open(fdest, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    dup2(fd, STDOUT_FILENO);
                    break;
                
                case 2 : 
                    fd = open(fdest, O_WRONLY | O_APPEND,0666);
                    dup2(fd, STDOUT_FILENO);
                    break;

                case 3:
                    fd = open(fdest, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    dup2(fd, STDERR_FILENO);
                    break;

                case 4:
                    fd = open(fdest, O_WRONLY | O_APPEND,0666);
                    dup2(fd, STDERR_FILENO);
                    break;

                default:
                    break;
                }
            }
            if(execvp(command,arg) == -1)
            {
                perror("Erreur : ");
                exit(EXIT_FAILURE);
            }
            if(strlen(fdest) > 0)
            {
                close(fd);
            }
            exit(EXIT_SUCCESS);
            break;
        default:
            if(!(flag==5))
                wait(&status);
            if (WIFEXITED(status))
                return EXIT_SUCCESS;
            return EXIT_FAILURE;
        }
}



extern char **environ;
/*
 * Mini interpreteur de commande
 * Lit une commande avec la fonction read_command
 * execute la commande avec run_command
 */
int main(int argc, char const *argv[])
{
    char command[BUFSIZE];
    char fdest[BUFSIZE];
    char* arg[BUFSIZE];
    int nb_args;
	if(argc > 1)
		DEBUG=1;
    while (1)
    {
		printf("minishell $ ");
        fdest[0] = '\0';
        int flag = 0;
        nb_args = read_command(command, arg, fdest, &flag);
        arg[0] = command;
        

        if (nb_args == -1)
        {
            printf("Exit\n");
            exit(EXIT_SUCCESS);
        }
        if(DEBUG) {
			printf(" ===>commande a exécuter: %s, %d arguments [",command,nb_args);
			for(int i=0; i<nb_args; i++)
				printf("%s , ",arg[i]);
			printf("], fdest : %s\n",fdest);
		}
		if(strncmp(arg[0],"mycd",5)==0){
			mycd(nb_args,arg[1]);
		}
		else if(strncmp(arg[0],"mypwd",6)==0){
			mypwd();
		}
		else if(strncmp(arg[0],"myenv",6)==0){
			for(int i = 0; environ[i] != NULL; i++){
				printf("%s\n",environ[i]);
			}
		}
		else if(strncmp(arg[0],"myexport",6)==0){
            if(nb_args != 2)
                printf("You must put an env_var\n");
            else
                putenv(arg[1]);
		}

        else{
            run_command(command,arg, fdest,flag);
        }
    }
    return EXIT_SUCCESS;
}
