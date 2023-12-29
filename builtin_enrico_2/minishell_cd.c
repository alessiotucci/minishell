/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:19:57 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/17 15:44:20 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void minishell_cd(char *directory) {
    if (directory == NULL) {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }

    printf("Changing directory to: %s\n", directory);

    // Verifica se il percorso esiste
    if (access(directory, F_OK) != 0) {
        perror("cd");
        return;
    }

    // Cambia la directory corrente
    if (chdir(directory) != 0) {
        perror("cd");
    } else {
        printf("Directory change successful!\n");
    }
}

int main(int argc, char *argv[]) {
    // Controlla che ci sia almeno un argomento
    if (argc > 1) {
        // Passa il primo argomento (il percorso) alla funzione
        minishell_cd(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
    }

    return 0;
}

