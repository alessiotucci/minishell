/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:33:57 by atucci            #+#    #+#             */
/*   Updated: 2023/12/29 16:57:41 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "..minishell.h"

void	minishell_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
}

/* Verifica se il percorso esiste, Cambia la directory corrente */
void	minishell_cd(char *directory)
{
	if (directory == NULL)
	{
		fprintf(stderr, "cd: missing argument\n");
		return ;
	}
	printf("Changing directory to: %s\n", directory);
	if (access(directory, F_OK) != 0)
	{
		perror("cd");
		return ;
	}
	if (chdir(directory) != 0)
		perror("cd");
	else
		printf("Directory change successful!\n");
}

void	minishell_echo(char *args[])
{
	int	i;
	int	suppress_newline;

	suppress_newline = 0;
	i = 1;
	if (args[1] != NULL && strcmp(args[1], "-n") == 0)
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
