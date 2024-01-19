/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:50:51 by atucci            #+#    #+#             */
/*   Updated: 2024/01/14 14:09:39 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	flag_for_echo(t_list_of_tok **head)
{
	char			*flag;
	t_list_of_tok	*current;
	char			*new_flag;

	current = *head;
	while (current != NULL)
	{
		if (current->type == T_FLAG
			&& current->previous->type == T_BUILTIN
			&& my_strcmp(current->previous->token, "echo") == 0)
		{
			flag = current->token;
			if (flag[0] == '-' && flag[1] == 'n' && flag[2] != '\0')
			{
				new_flag = malloc(3 * sizeof(char));
				if (new_flag == NULL)
					printf("Memory allocation failed\n");
				new_flag[0] = '-';
				new_flag[1] = 'n';
				new_flag[2] = '\0';
				free(current->token);
				current->token = new_flag;
			}
		}
		current = current->next;
	}
}

/*Fully process is a function needed to find command arguments and other stuff*/
void	update_token_types(t_list_of_tok **head)
{
	t_list_of_tok	*current;
	t_list_of_tok	*prev;

	flag_for_echo(head);
	prev = NULL;
	current = *head;
	while (current != NULL)
	{
		if (prev != NULL
			&& (prev->type == T_COMMAND
				|| prev->type == T_FLAG
				|| prev->type == T_BUILTIN
				|| prev->type == T_COMMAND_ARGS)
			&& current->type == T_COMMAND)
			current->type = T_COMMAND_ARGS;
		else if (prev != NULL
			&& (prev->type == T_REDIR_APP
				|| prev->type == T_REDIR_IN
				|| prev->type == T_REDIR_OUT
				|| prev->type == T_HERE_DOC))
			current->type = T_FILE_NAME;
		prev = current;
		current = current->next;
	}
}

t_type_of_tok	type_of_token(char *spitted)
{
	if (is_pipe(spitted))
		return (T_PIPES);
	else if (is_parent(spitted))
		return (T_PARENT);
	else if (is_flag(spitted))
		return (T_FLAG);
	else if (is_file_reader(spitted))
		return (T_REDIR_IN);
	else if (is_file_writer(spitted))
		return (T_REDIR_OUT);
	else if (is_here_doc(spitted))
		return (T_HERE_DOC);
	else if (is_file_appender(spitted))
		return (T_REDIR_APP);
	else if (is_dollar(spitted))
		return (T_DOLLAR);
	else if (is_logical_op(spitted))
		return (T_LOGIC_OPERAR);
	else if (is_builtin(spitted))
		return (T_BUILTIN);
	else
		return (T_COMMAND);
}
