// my_exit.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void cleanupResources() {
    // Aggiungi qui la tua logica di pulizia delle risorse
    // Ad esempio, chiudi file, dealloca memoria, ecc.
    printf("Pulizia delle risorse...\n");
}

void handleSignal(int signal) {
    // Gestisci i segnali, se necessario
    printf("Ricevuto il segnale %d\n", signal);
    cleanupResources();
    exit(1);
}

void minishellExit(int exitCode) {
    // Pulizia delle risorse prima dell'uscita
    cleanupResources();

    // Termina i processi figli
    pid_t childPid;
    while ((childPid = waitpid(-1, NULL, WNOHANG)) > 0) {
        printf("Processo figlio %d terminato\n", childPid);
    }

    // Altre azioni personalizzate, se necessario
    printf("Uscita con codice %d\n", exitCode);

    // Uscita dal programma
    exit(exitCode);
}


