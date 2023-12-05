/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:17:12 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/05 17:17:33 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int minishell_echo(char **args) {
    int i = 1;

    while (args[i] != NULL) {
        printf("%s", args[i]);

        // Stampa uno spazio tra gli argomenti (tranne l'ultimo)
        if (args[i + 1] != NULL) {
            printf(" ");
        }

        i++;
    }

    // Stampa un carattere di nuova riga alla fine
    printf("\n");

    return 0;  // Ritorna il codice di uscita appropriato
}
