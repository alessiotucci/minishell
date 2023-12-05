/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:23:29 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/05 17:39:51 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

nt minishell_export(char **args, t_env **env_list) 
{
    if (args[1] == NULL) 
    {
        // Se manca l'argomento, visualizza tutte le variabili d'ambiente
        t_env *current = *env_list;
        while (current != NULL) {
            printf("%s=%s\n", current->key, current->value);
            current = current->next;
        }
    } 
    else 
    {
        // Se ci sono argomenti, imposta o aggiorna le variabili d'ambiente
        char *variable = args[1];

        // Trova l'uguale per separare il nome della variabile e il valore
        char *equal_sign = strchr(variable, '=');

        if (equal_sign != NULL) 
        {
            // Divide il nome della variabile e il valore
            *equal_sign = '\0';
            char *value = equal_sign + 1;

            // Aggiorna o imposta la variabile d'ambiente
            setenv(variable, value, 1);
        } 
        else 
        {
            // Se non c'è un segno di uguale, visualizza un messaggio di errore
            fprintf(stderr, "minishell: export: invalid syntax\n");
        }
    }

    return 0;  // Ritorna il codice di uscita appropriato
}
