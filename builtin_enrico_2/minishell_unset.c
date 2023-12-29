/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:16:44 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/29 16:17:19 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void minishell_unset(char *args[]) 
{
    // Check if there are arguments to unset
    if (args[1] == NULL) 
    {
        fprintf(stderr, "minishell_unset: Missing argument\n");
        return;
    }

    // Iterate through the arguments and unset environment variables
    for (int i = 1; args[i] != NULL; i++) 
    {
        if (unsetenv(args[i]) != 0) {
            perror("minishell_unset");
        }
    }
}

int main(int argc, char *argv[]) 
{
    minishell_unset(argv);

    return 0;
}
