/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:50:51 by atucci            #+#    #+#             */
/*   Updated: 2023/12/27 11:30:29 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Fully process is a function needed to find command arguments and other stuff*/
void	update_token_types(t_list_of_tok **head)
{
	t_list_of_tok *current = *head;
	t_list_of_tok *prev = NULL;

	while (current != NULL)
	{
		if (prev != NULL
			&& (prev->type == T_COMMAND || prev->type == T_FLAG || prev->type == T_BUILTIN)
			&& current->type == T_COMMAND)
			current->type = T_COMMAND_ARGS;
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
