#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

/*
 * NOM : PENA CAMPOS
 * PRENOM : Mateo
 */


// remplacer LOGIN par votre nom de LOGIN INSA
int mpenacam(int argc, char** argv)
{
	uid_t uid, gid;
    struct passwd *pass;
    struct group *gr;
    uid = getuid();
    gid = getgid();
    pass = getpwuid(uid);
    gr = getgrgid(gid);
    printf("uid=%d(%s) gid=%d(%s)\n", (int)uid, pass->pw_name, (int)gid, gr->gr_name);
    return EXIT_FAILURE;
}




// remplacer LOGIN par votre nom de LOGIN INSA
int main(int argc, char ** argv) {

	return mpenacam(argc, argv);
}
