/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:33:57 by atucci            #+#    #+#             */
/*   Updated: 2024/01/21 20:24:51 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
}

/* Get the current working directory before changing directories
 * TO_DO: we need to update the env for the current folder
 */
void	minishell_cd(char *directory, char **env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		my_setenv(env, "OLDPWD", cwd, 0);
	if (directory == NULL)
		return (print_and_update("cd: missing argument\n", 1, 1));
	if (access(directory, F_OK) != 0)
		return (print_and_update("cd: no such file or directory\n", 1, 1));
	if (chdir(directory) != 0)
		print_and_update("cd: error changing directory\n", 1, 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		my_setenv(env, "PWD", cwd, 0);
}

/* the flag is being check in the parsing process
 * adding the support for the -nnn and the -n */
void	minishell_echo(char *args[])
{
	int	i;
	int	suppress_newline;

	suppress_newline = 0;
	i = 1;
	if (args[1] != NULL && my_strcmp(args[1], "-n") == 0)
	{
		suppress_newline = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!suppress_newline)
		printf("\n");
}
