/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:51:40 by atucci            #+#    #+#             */
/*   Updated: 2024/01/20 17:45:48 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* build in functions 
void	minishell_pwd(void);
void	minishell_cd(char *directory);
void	maxishell_echo(char *args[]);
void	maxishell_export(char *args[]);
void	maxishell_env(char *args[])
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
//		minishell_export(args);
		my_export(args, env);
	else if (my_strcmp(node->token, "unset") == 0)
		minishell_unset(args[1], env);
	else if (my_strcmp(node->token, "env") == 0)
		minishell_env(env);
	else if (my_strcmp(node->token, "exit") == 0)
		minishell_exit(args); // what value give to this? 
	return (NULL);
}

