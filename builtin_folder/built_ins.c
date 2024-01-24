/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:13:21 by atucci            #+#    #+#             */
/*   Updated: 2024/01/24 17:32:54 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "built_ins.h"
/*
extern long long	g_exit_status;

static void	exit_non_numeric_arg(void)
{
	g_exit_status = 2;
	write(STDERR_FILENO, EXIT_NON_NUMERIC_ARG, ft_strlen(EXIT_NON_NUMERIC_ARG));
	write(STDERR_FILENO, "\n", 1);
}

void	cmd_exit(t_statement *s)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (s->argc == 2)
	{
		if (is_all_digits_or_signals(s->argv[1]))
		{
			if (!fits_in_longlong(s->argv[1]))
				exit_non_numeric_arg();
			else
				g_exit_status = ft_atoll(s->argv[1]);
		}
		else
			exit_non_numeric_arg();
	}
	else if (s->argc > 2)
	{
		g_exit_status = EXIT_FAILURE;
		write(STDERR_FILENO, EXIT_TOO_MANY_ARGS, ft_strlen(EXIT_TOO_MANY_ARGS));
		write(STDERR_FILENO, "\n", 1);
	}
	else
		g_exit_status = EXIT_SUCCESS;

	exit(g_exit_status);
}
*/

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
		//for (char **p = env; *p != NULL; p++)
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


/* If no arguments provided, print the current environment variables */
void minishell_export(char *args[]) 
{
	int			i;
	char		**key_value;
	char		**env;
	extern char	**environ;

	if (args[1] == NULL) 
	{
		env = environ;
		while (*env != NULL) 
		{
			printf("%s\n", *env);
			env++;
		}
	}
	else
	{
		i = 1;
		while (args[i] != NULL) 
		{
			key_value = ft_split(args[i], '=');
			if (key_value && key_value[0] && key_value[1]) 
			{
				if (setenv(key_value[0], key_value[1], 1) != 0) 
					perror("minishell_export");
				free(key_value);
			}
			else
				printf("minishell_export: Invalid format: %s\n", args[i]);
			i++;
		}
	}
}

/* If no arguments provided, print the current environment variables
 * we need to double check this case
 */
void	minishell_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s \n", env[i]);
		i++;
	}
}

void	try_builtin(void)
{
	builtin1();
	builtin2();
	builtin3();
	return ;
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
