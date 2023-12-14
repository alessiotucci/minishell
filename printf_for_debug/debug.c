/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:47:07 by atucci            #+#    #+#             */
/*   Updated: 2023/12/14 11:07:26 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
const char *names[] =
{
	"Command",
	"Flag",
	"Builtin",
	"Parenthesis",
	"Dollar",
	"Pipes",
	"Redirection in",
	"Redirection out",
	"Redirection appender",
	"Redirection delimiter",
	"Logical Operator"
};

const char *colors[] =
{
	BLUE,
	PURPLE,
	GRAY,
	GREEN,
	CYAN,
	YELLOW,
	RED,
	BG_GREEN,
	BG_CYAN,
	BG_YELLOW,
	BG_RED
};

void print_list_tokens(t_list_of_tok **head)
{
	t_list_of_tok *current = *head;
	while (current != NULL)
	{
		printf("\n|--------------------|\n");
		printf("|ADDS %p |\n", current);
		printf("|String %s\n", current->command_as_string);
		printf("|%sPRIORITY %s%d\n", RED, RESET, current->priority_lev);
		printf("|TYPE %d,  %s%s%s\n",current->type, colors[current->type], names[current->type], RESET);
		printf("|PREV %p \n", current->previous);
		printf("|NEXT %p \n", current->next);
		printf("|INDEX %d\n", current->index);
		printf("|--------------------|\n\n");
		current = current->next;
	}
}

