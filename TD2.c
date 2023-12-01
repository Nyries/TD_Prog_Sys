#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
    struct stat sb;
    if (stat(argv[1],&sb)==-1){
        perror("stat");
        exit(EXIT_FAILURE);
    }
    if (S_ISREG(sb.st_mode)){
        printf("C'est un fichier ordinaire, sa taille vaut %ld o.\n",sb.st_size);
    } else {
        printf("Ceci n'est pas un fichier ordinaire.\n");
    }
    exit(EXIT_SUCCESS);
}