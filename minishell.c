/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2024/01/21 17:03:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backlash);
}

//env_copy
char	**copy_array(char **env, int extra_space)
{
	int		env_count;
	char	**env_copy;
	int		i;

	env_count = 0;
	while (env[env_count] != NULL)
		env_count++;
	env_copy = (char **)malloc((env_count + extra_space + 1) * sizeof(char *));
	if (env_copy == NULL)
		return (perror("Error in memory allocation"), NULL);
	i = 0;
	while (env[i] != NULL)
	{
		env_copy[i] = ft_strdup(env[i]);
		if (env_copy[i] == NULL)
			return (perror("Error in memory allocation"), NULL);
		i++;
	}
	while (i < env_count + extra_space)
	{
		env_copy[i] = NULL;
		i++;
	}
	env_copy[env_count + extra_space] = NULL;
	return (env_copy);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*input;
	char	**env_copy;
	int		g_exit_status = 0;  // define g_exit_status

	(void)ac;
	(void)av;
	(void)g_exit_status;
	env_copy = copy_array(envp, 0);
	set_g_exit(0);
	while (1)
	{
		handle_signal();
		input = readline(RED"minishell% "RESET);
		if (input && input[0])
			add_history(input); // double check for the history
		if (input == NULL)
			return (0 * write(1, "\n", 1));
		if (input != NULL && lexer(input, env_copy) == 1)
			continue ;
			//return (1);
	}
	free_string_array(env_copy);
}
