/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:51:40 by atucci            #+#    #+#             */
/*   Updated: 2024/01/04 11:32:06 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* build in functions 
void	minishell_pwd(void);
void	minishell_cd(char *directory);
void	minishell_echo(char *args[]);
void	minishell_export(char *args[]);
void	minishell_env(char *args[])
 function for the executor */
#include "../minishell.h"

void	*which_built_in(t_list_of_tok *node, char **args, char **env)
{
	(void)env;
	if (node == NULL)
		return (NULL);
	if (my_strcmp(node->token, "echo") == 0)
		minishell_echo(args);
	else if (my_strcmp(node->token, "cd") == 0)
			minishell_cd(args[1]);
	else if (my_strcmp(node->token, "pwd") == 0)
		minishell_pwd();
	else if (my_strcmp(node->token, "export") == 0)
	//	return NULL;
		minishell_export(args);
	else if (my_strcmp(node->token, "unset") == 0)
		return NULL;
	//	minishell_unset();
	else if (my_strcmp(node->token, "env") == 0)
		return NULL;//minishell_env();
	else if (my_strcmp(node->token, "exit") == 0)
		return NULL;//minishell_exit();
	return (NULL);
}

