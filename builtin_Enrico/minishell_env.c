/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    minishell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:42 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/05 17:27:32 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int minishell_env(t_env *env_list) 
{
    // Stampa tutte le variabili d'ambiente
    t_env *current = env_list;
    while (current != NULL) 
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }

    return 0;  // Ritorna il codice di uscita appropriato
}
