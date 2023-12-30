/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:16:44 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/30 10:24:13 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void minishell_unset(char *args[]) 
{
    // Check if there are arguments to unset
    if (args[1] == NULL)
    {
        printf("minishell_unset: Missing argument\n");
        return;
    }

    // Unset the first argument
    if (unsetenv(args[1]) != 0) 
    {
        printf("minishell_unset: Error unsetting %s\n", args[1]);
    }

    // If there are more arguments, unset them one by one
    int i = 2;
    while (args[i] != NULL) 
    {
        if (unsetenv(args[i]) != 0) 
        {
            printf("minishell_unset: Error unsetting %s\n", args[i]);
        }
        i++;
    }
}

int main(int argc, char *argv[]) 
{
    minishell_unset(argv);

    return 0;
}
