#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 256

void display_file(const char *filepath){
    int fd = open(filepath,O_RDONLY);
    if(fd==-1){
        perror("Erreur à l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFSIZE];
    ssize_t  bytesRead;

    while ((bytesRead=read(fd,buffer,sizeof(buffer)))>0){
        if (write(STDOUT_FILENO,buffer,sizeof(buffer))!=bytesRead){
            perror("Erreur lors de l'écriture sur la console");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    close(fd);
}
void copy_file(const char *source, const char *destination){
    int source_fd = open(source, O_RDONLY);
    if (source_fd==-1){
        perror("Erreur lors de l'ouverture du fichier source");
        exit(EXIT_FAILURE);
    }
    struct stat st;
    if (stat(destination,&st)==0){
        fprintf(stderr,"Le fichier destination existe déjà.\n");
        close(source_fd);
        exit(EXIT_FAILURE);
    }
    int dest_fd= open(destination,O_WRONLY|O_CREAT|O_EXCL,st.st_mode);
    if(dest_fd==-1){
        perror("Erreur lors de l'ouverture ou de la création du fichier");
        close(dest_fd);
        exit(EXIT_FAILURE);
    }
    char buffer[BUFSIZE];
    ssize_t bytesRead;
    while ((bytesRead=read(dest_fd,buffer,sizeof(buffer)))>0){
        if (write(STDOUT_FILENO,buffer,sizeof(buffer))!=bytesRead){
            perror("Erreur lors de l'écriture sur la console");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }
    close(source_fd);
    close(dest_fd);
    printf("Copie réussiee de %s vers %s.\n",source ,destination);
}

int main(int argc,char *argv[]){
    if (argc!=4 && argc!=3){
        fprintf(stderr,"Usage: %s <fichier1> <fichier2>",argv[0]);
        exit(EXIT_FAILURE);
    }
    const char *source = argv[2];
    if (strcmp(argv[1],"my_cp")==0) {
        if (argc == 3) {
            display_file(source);
        } else {
            const char *destination = argv[3];
            copy_file(source, destination);
        }
    }
    return EXIT_SUCCESS;
}