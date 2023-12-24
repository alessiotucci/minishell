/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2023/12/24 15:13:57 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path_env(char **env)
{
	int	i;
	char *nully = NULL;
	(void)env;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			nully = env[i] + 5;
			break ;
		}
		i++;
	}
	printf("path env: |%s%s%s|\n",YELLOW, nully, RESET);
	return (nully);
}

void	executor(t_list_of_tok **head, char **envp)
{
	(void)head;
	find_path_env(envp);
	executor2();
	executor3();
	return ;
}
