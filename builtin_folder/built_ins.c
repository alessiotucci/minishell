/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:13:21 by atucci            #+#    #+#             */
/*   Updated: 2023/12/29 17:00:00 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "built_ins.h"

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

/* If no arguments provided, print the current environment variables */
void	minishell_export(char *args[])
{
	if (args[1] == NULL)
	{
		extern char **environ;
		for (char **env = environ; *env != NULL; env++)
		{
			printf("%s\n", *env);
		}
	}
	else
	{
		// Iterate through the arguments and set environment variables
		for (int i = 1; args[i] != NULL; i++)
		{
			char *key = strtok(args[i], "=");
			char *value = strtok(NULL, "");
			// Check if the format is key=value
			if (key != NULL && value != NULL)
			{
				if (setenv(key, value, 1) != 0)
					perror("minishell_export");
			}
			else
				fprintf(stderr, "minishell_export: Invalid format: %s\n", args[i]);
		}
	}
}

/* If no arguments provided, print the current environment variables */
void	minishell_env(char *args[])
{
	if (args[1] == NULL)
	{
		extern char **environ;
		for (char **env = environ; *env != NULL; env++)
		{
			printf("%s\n", *env);
		}
	}
	else
		fprintf(stderr, "minishell_env: Too many arguments\n");
}
void	try_builtin(void)
{
	builtin1();
	builtin2();
	builtin3();
	return ;
}
