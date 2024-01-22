/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2024/01/22 14:11:08 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 5 */
t_list_of_tok	*find_first_occurrence(t_list_of_tok *head, t_type_of_tok enum_value)
{
	t_list_of_tok	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == enum_value)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/* 4 Check if the previous node is valid */
int	is_valid_prev(t_list_of_tok *node)
{
	if (node == NULL || (node->type != T_BUILTIN
			&& node->type != T_COMMAND
			&& node->type != T_FLAG
			&& node->type != T_COMMAND_ARGS))
		return (0);
	else
		return (1);
}

/* 3 Check if the next node is valid */
int	is_valid_next(t_list_of_tok *node)
{
	if (node == NULL || (node->type != T_COMMAND
			&& node->type != T_FLAG
			&& node->type != T_COMMAND_ARGS))
		return (0);
	else
		return (1);
}

/* 2 Check if the next node is a command,
 * built-in, or followed by a command/built-in */
int	is_command_or_builtin(t_list_of_tok *node)
{
	if (node == NULL || (node->type != T_COMMAND
			&& node->type != T_BUILTIN
			&& node->type != T_FILE_NAME))
		return (0);
	else if (node->type == T_FILE_NAME && (node->next->type == T_COMMAND
			|| node->next->type == T_BUILTIN
			|| is_a_redirection(node->next)))
		return (2);
	else
		return (1);
}

/* 1 */
void	move_node(t_list_of_tok **head, t_list_of_tok *target, t_list_of_tok *mov)
{
	t_list_of_tok	*sublist_end;

	sublist_end = mov;
	while (sublist_end->next && sublist_end->next->type != T_REDIR_OUT && sublist_end->next->type != T_REDIR_IN && sublist_end->next->type != T_REDIR_APP && sublist_end->next->type != T_PIPES)
		sublist_end = sublist_end->next;
	if (*head == mov)
		*head = mov->next;
	if (mov->previous != NULL)
		mov->previous->next = sublist_end->next;
	if (sublist_end->next != NULL)
		sublist_end->next->previous = mov->previous;
	mov->previous = target->previous;
	sublist_end->next = target;
	if (target->previous != NULL)
		target->previous->next = mov;
	target->previous = sublist_end;
	if (*head == target)
		*head = mov;
}
