/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:51:40 by atucci            #+#    #+#             */
/*   Updated: 2023/12/29 17:05:20 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* build in functions 
void	minishell_pwd(void);
void	minishell_cd(char *directory);
void	minishell_echo(char *args[]);
void	minishell_export(char *args[]);
void	minishell_env(char *args[])
 function for the executor */


void	which_built_in(t_list_of_tok *node)
{
	if (node == NULL)
		return;
	if (my_strcmp(node->command, "echo") == 0)
		minishell_echo();
	else if (my_strcmp(node->command, "cd") == 0)
		minishell_cd();
	else if (my_strcmp(node->command, "pwd") == 0)
		minishell_pwd();
	else if (my_strcmp(node->command, "export") == 0)
		minishell_export();
	else if (my_strcmp(node->command, "unset") == 0)
		minishell_unset();
	else if (my_strcmp(node->command, "env") == 0)
		minishell_env();
	else if (my_strcmp(node->command, "exit") == 0)
		minishell_exit();
}

