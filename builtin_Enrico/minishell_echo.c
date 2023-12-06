/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:26:24 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/06 17:26:45 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int minishell_echo(char **args) 
{
    int i = 1;

    // Gestisci l'opzione -n, se presente
    if (args[i] != NULL && strcmp(args[i], "-n") == 0) 
    {
        // Ignora il carattere di nuova riga alla fine
        i++;
    }

    while (args[i] != NULL) 
    {
        printf("%s", args[i]);

        // Stampa uno spazio tra gli argomenti (tranne l'ultimo)
        if (args[i + 1] != NULL) 
        {
            printf(" ");
        }

        i++;
    }

    // Stampa un carattere di nuova riga solo se l'opzione -n non è stata specificata
    if (args[1] == NULL || (args[1] != NULL && strcmp(args[1], "-n") != 0)) 
    {
        printf("\n");
    }

    return 0;  // Ritorna il codice di uscita appropriato
}
