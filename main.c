#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
    int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int fd[2];

    //Apriamo la pipe, se ritorna -1 è avvenuto un errore
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(-1);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("errore fork");
        exit(-2);
    }
    // Processo Figlio
    if (!pid) {
        //Chiudiamo il file descriptor che non usiamo
        close(fd[0]);
        int somma = 0;
        for (int i = 0; i < 10; i++) {
            if (arr[i] % 2 == 0) {
                somma += arr[i];
            }
        }
        write(fd[1], somma, sizeof(somma));
        close(fd[1]);
        exit(0);
    }
    close(fd[1]);
    //padre
    int somma2 = 0;
    for (int i = 0; i < 10; i++) {
        if (arr[i] % 2 != 0) {
            somma2 += arr[i];
        }
    }
    read(fd[0], somma, sizeof(somma));
    close (fd[0]);

    return 0;
}