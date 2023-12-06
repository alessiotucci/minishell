/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:24:56 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/05 17:42:17 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int minishell_unset(char **args, t_env **env_list) 
{
    if (args[1] == NULL) 
    {
        // Se manca l'argomento, visualizza un messaggio di errore
        fprintf(stderr, "minishell: unset: missing argument\n");
    } 
    else 
    {
        // Rimuovi la variabile d'ambiente specificata
        unsetenv(args[1]);

        // Rimuovi la variabile d'ambiente dalla lista interna, se presente
        t_env *current = *env_list;
        t_env *prev = NULL;

        while (current != NULL) 
        {
            if (strcmp(current->key, args[1]) == 0) 
            {
                // Rimuovi il nodo dalla lista
                if (prev != NULL) 
                {
                    prev->next = current->next;
                } else 
                {
                    *env_list = current->next;
                }

                // Libera la memoria
                free(current->key);
                free(current->value);
                free(current);

                break;
            }

            prev = current;
            current = current->next;
        }
    }

    return 0;  // Ritorna il codice di uscita appropriato
}
