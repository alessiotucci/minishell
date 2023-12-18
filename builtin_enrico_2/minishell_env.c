/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:05:47 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/17 22:06:31 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_env(t_data *data) {
    t_vlst *current = data->envp_lst;

    while (current != NULL) {
        ft_putstr_fd(current->var_name, STDOUT_FILENO);
        ft_putchar_fd('=', STDOUT_FILENO);
        ft_putendl_fd(current->var_value, STDOUT_FILENO);
        current = current->next;
    }
}

//main_trial
int main() 
{
    // Supponiamo che tu abbia già inizializzato e popolato la lista delle variabili d'ambiente (data->envp_lst)
    
    minishell_env(data);

    return 0;
}
