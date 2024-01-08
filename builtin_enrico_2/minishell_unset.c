/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:16:44 by enricogiral       #+#    #+#             */
/*   Updated: 2024/01/08 16:15:31 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    if (argc != 2) {
        printf("Usage: %s VARIABLE_NAME\n", argv[0]);
        return 1;
    }

    // Trova la variabile nell'ambiente
    char *variable_name = argv[1];
    char **env = envp;
    int found = 0;

    while (*env != NULL) {
        if (strncmp(*env, variable_name, strlen(variable_name)) == 0 &&
            (*env)[strlen(variable_name)] == '=') {
            found = 1;
            break;
        }
        env++;
    }

    // Se la variabile è stata trovata, rimuovila
    if (found) {
        for (char **p = env; *p != NULL; p++) {
            *p = *(p + 1);
        }
        printf("Unset variable: %s\n", variable_name);
    } else {
        printf("Variable not found: %s\n", variable_name);
    }

    return 0;
}
