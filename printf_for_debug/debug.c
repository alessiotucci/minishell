/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:47:07 by atucci            #+#    #+#             */
/*   Updated: 2023/12/09 15:01:10 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
const char *tok_names[] =
{
	"Command",
	"Flag",
	"Builtin",
	"Dollar",
	"Pipes",
	"Redirection in",
	"Redirection out",
	"Redirection appender",
	"Redirection delimiter",
	"Logical Operator"
};

void print_list_tokens(t_list_of_tok **head)
{
	t_list_of_tok *current = *head;
	while (current != NULL)
	{
		printf("\n|--------------------|\n");
		printf("|ADDS %p |\n", current);
		printf("|CMD %s\n", current->command_as_string);
		printf("|TYPE %s%s%s\n", RED, tok_names[current->type], RESET);
		printf("|PREV %p \n", current->previous);
		printf("|NEXT %p \n", current->next);
		printf("|INDEX %d\n", current->index);
		printf("|--------------------|\n\n");
		current = current->next;
	}
}

