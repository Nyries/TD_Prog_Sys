#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void print_PCB() {
    printf("PCB | PPID: %d\n", getppid());
    printf("    | PID: %d\n", getpid());
    printf("    | UID: %d\n", getuid());
    printf("    | GID: %d\n", getgid());
}


int main() {
    pid_t ret = fork();

    // Test pour savoir si on renvoie le père, le fils ou rien
    if (ret == -1) {
        exit(EXIT_FAILURE);
    }

    if (ret == 0) {
        printf("Child process:\n");
    }

    else {
        printf("Parent process:\n");
    }

    print_PCB();
    exit(EXIT_SUCCESS);
}
