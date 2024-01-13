/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2024/01/13 12:39:16 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backlash);
}

//env_copy
// invece che uscire con errore, ritornare null (?)
static char	**copy_array(char **env)
{
	int		env_count;
	char	**env_copy;
	int		i;

	env_count = 0;
	while (env[env_count] != NULL)
		env_count++;
	env_copy = (char **)malloc((env_count + 1) * sizeof(char *));
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
	env_copy[env_count] = NULL;
	return (env_copy);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*input;
	char **env_copy;

	(void)ac;
	(void)av;
	env_copy = copy_array(envp);
	while (1)
	{
		handle_signal();
		input = readline(RED"minishell% "RESET);
		add_history(input);
		if (input == NULL)
			return (0 * write(1, "\n", 1));
		if (input != NULL && lexer(input, env_copy) == 1)
			return (1);
	// what we need to return for syntax error? 
	//	token();
	//	parser();
	//	try_builtin();
	}
}
