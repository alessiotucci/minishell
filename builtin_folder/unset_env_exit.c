/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiotucci   <atucci@student.42>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:13:21 by atucci            #+#    #+#             */
/*   Updated: 2024/03/26 11:51:44 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "built_ins.h"

// Function to implement the 'unset' built-in
void minishell_unset(char *var_name, char *envp[]) 
{
	char	**env;
	int		found;
	char	**p;

	found = 0;
	env = envp;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, var_name, ft_strlen(var_name)) == 0 &&
			(*env)[ft_strlen(var_name)] == '=')
		{
			found = 1;
			break;
		}
		env++;
	}
	if (found)
	{
		p = env;
		while (*p != NULL)
		{
			*p = *(p + 1);
			p++;
		}
		printf("Unset variable: %s\n", var_name);
	}
	else
		printf("Variable not found: %s\n", var_name);
}

/* If no arguments provided, print the current environment variables
 * we need to double check this case
 */
void	minishell_env(char **env)
{
	// you can simply this and delete
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s \n", env[i]);
		i++;
	}
}

void	handle_signal(int signal)
{
	printf("signal receive%d\n", signal);
	exit(1);
}

void	minishell_exit(char **arg)
{
	int		exit_code;

	if (arg[1])
		exit_code = ft_atoi(arg[1]);
	else
		exit_code = g_exit_status;
	printf("exit with code %d\n", exit_code);
	exit(exit_code);
}
