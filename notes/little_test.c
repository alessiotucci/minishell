/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:03:32 by atucci            #+#    #+#             */
/*   Updated: 2024/01/09 17:27:50 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
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




void minishellExit(int exitCode);

// commenzo
int	main(void)
{
	char	*input;
	
	while (1)
	{
		input = readline("minishelly>");
		 // Verifica se l'utente ha inserito "exit" come comando
        if (strcmp(input, "exit") == 0)
        {
            // Chiamata alla tua funzione di uscita personalizzata
            minishellExit(0);
        }
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
