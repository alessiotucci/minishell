// my_exit.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void cleanupResources() {
    printf("Pulizia delle risorse...\n");
}

void handleSignal(int signal) {
    printf("Ricevuto il segnale %d\n", signal);
    cleanupResources();
    exit(1);
}

void minishellExit(int exitCode) {
    cleanupResources();

    // Termina i processi figli
    pid_t childPid;
    while ((childPid = waitpid(-1, NULL, WNOHANG)) > 0) {
        printf("Processo figlio %d terminato\n", childPid);
    }

    printf("Uscita con codice %d\n", exitCode);

    // Uscita dal programma
    exit(exitCode);
}
