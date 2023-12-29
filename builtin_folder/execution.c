/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:51:40 by atucci            #+#    #+#             */
/*   Updated: 2023/12/29 18:37:03 by atucci           ###   ########.fr       */
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

void	*which_built_in(t_list_of_tok *node)
{
	if (node == NULL)
		return (NULL);
	if (my_strcmp(node->command_as_string, "echo") == 0)
		return NULL;//minishell_echo();
	else if (my_strcmp(node->command_as_string, "cd") == 0)
		minishell_cd(node->next->command_as_string);
	else if (my_strcmp(node->command_as_string, "pwd") == 0)
		minishell_pwd();
	else if (my_strcmp(node->command_as_string, "export") == 0)
		return NULL;//minishell_export();
	else if (my_strcmp(node->command_as_string, "unset") == 0)
		return NULL;//minishell_unset();
	else if (my_strcmp(node->command_as_string, "env") == 0)
		return NULL;//minishell_env();
	else if (my_strcmp(node->command_as_string, "exit") == 0)
		return NULL;//minishell_exit();
	return (NULL);
}

