/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:33:57 by atucci            #+#    #+#             */
/*   Updated: 2024/01/09 16:30:56 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_pwd(void)
{
//	printf("%sour implementation of pwd:%s\n", GREEN, RESET);
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
}

/* Verifica se il percorso esiste, Cambia la directory corrente
 Se non viene specificato un percorso, porta alla directory home
 TO_DO: we need to update the env for the current folder
 */
void	minishell_cd(char *directory)
{
	if (directory == NULL)
	{
		fprintf(stderr, "cd: missing argument\n");
		return ;
	}
	//printf("Changing directory to: %s%s%s\n",YELLOW, directory, RESET);
	if (access(directory, F_OK) != 0)
	{
		perror("cd");
		return ;
	}
	if (chdir(directory) != 0)
		perror("cd");
	//else
	//	printf("%sDirectory change successful!%s\n", GREEN, RESET);
}
/* adding the support for the -nnn and the -n */
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
