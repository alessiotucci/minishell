/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:29:00 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/05 17:44:13 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "builtin.h"
#include "minishell.h"

int main(void) {
    char input[1024];

    // Loop principale
    while (1) {
        // Legge l'input dall'utente
        printf("minishell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Uscita se l'utente preme CTRL+D
        }

        // Rimuove il carattere di nuova riga finale
        input[strcspn(input, "\n")] = '\0';

        // Suddivide l'input in argomenti
        char *args[1024];
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; // Segna la fine dell'array di argomenti

        // Verifica se l'utente ha inserito un comando built-in
        if (arg_count > 0) {
            if (strcmp(args[0], "echo") == 0) {
                minishell_echo(args);
            } else if (strcmp(args[0], "cd") == 0) {
                minishell_cd(args);
            } else if (strcmp(args[0], "pwd") == 0) {
                minishell_pwd();
            } else if (strcmp(args[0], "export") == 0) {
                minishell_export(args);
            } else if (strcmp(args[0], "unset") == 0) {
                minishell_unset(args);
            } else if (strcmp(args[0], "env") == 0) {
                minishell_env();
            } else {
                // Se il comando non è built-in, puoi implementare la logica per eseguire comandi esterni
                // ...
            }
        }
    }

    return 0;
}
