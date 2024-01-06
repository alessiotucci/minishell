/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2024/01/06 18:26:36 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c); 
	signal(SIGQUIT, handle_ctrl_backlash); 
}

//env_copy
static char **copy_array(char **env) 
{
    int env_count = 0;
    while (env[env_count] != NULL)
        env_count++;

    char **env_copy;

	env_copy = (char **)malloc((env_count + 1) * sizeof(char *));
    if (env_copy == NULL) 
	{
        perror("Errore in memory allocation");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (env[i] != NULL) 
	{
        env_copy[i] = strdup(env[i]);
        if (env_copy[i] == NULL) 
		{
            perror("Errore in memory allocation");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    env_copy[env_count] = NULL;

    return env_copy;
}

// Funzione per liberare la memoria dell'array di copia delle variabili di ambiente
static void free_array(char **arr) 
{
    int i = 0;
    while (arr[i] != NULL) 
	{
        free(arr[i]);
        i++;
    }
    free(arr);
}

int	main(int ac, char *av[], char *envp[])
{
//	int		count;
	char	*input;

//	count = 1;
	if (ac || av || envp)
		ft_printf("\n");
	
	char **env_copy;
	env_copy = copy_array(envp);

	while (1)
	{
		handle_signal();
		input = readline(RED"minishell% "RESET);
		add_history(input);
		if (input == NULL)
			return (0 * write(1, "\n", 1));
		if (input != NULL && lexer(input, envp) == 1)
			return (1);
	// what we need to return for syntax error? 
	//	token();
	//	parser();
	//	try_builtin();
	}
}
