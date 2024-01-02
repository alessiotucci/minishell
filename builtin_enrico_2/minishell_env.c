/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:05:47 by enricogiral       #+#    #+#             */
/*   Updated: 2024/01/02 16:25:24 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void    minishell_env(char **env) 
{
    // If no arguments provided, print the current environment variables
    
    int i = 0;
    while (env[i])
    {
        printf("%s \n", env[i]);
        i++;
    }
    /*if (env[1] == NULL) 
    {
        extern char **environ;
        char **env = environ;
        while (*env != NULL) 
        {
            printf("%s\n", *env);
            env++;
        }
    } 
    else 
    {
        fprintf(stderr, "minishell_env: Too many arguments\n");
    }*/
}

int main(int argc, char **argv, char **env) 
{
    minishell_env(env);
    return 0;
}


