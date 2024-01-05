/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:47:07 by atucci            #+#    #+#             */
/*   Updated: 2024/01/05 17:16:08 by atucci           ###   ########.fr       */
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
	"Here Documents",
	"Logical Operator",
	"Command Arguments",
	"File Name "
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
	BG_RED,
	RESET,
	RESET
};

void	print_node(t_list_of_tok *node)
{
	printf("\n|--------------------|\n");
	printf("|ADDS %p |\n",node);
	printf("|\t%s\n", node->token);
	printf("|  %s%s%s\n", colors[node->type], names[node->type], RESET);
	printf("|%sPRIORITY %s%d\n", RED, RESET, node->priority_lev);
	printf("|PREV %p \n",node->previous);
	printf("|NEXT %p \n",node->next);
//	if (node->next != NULL)
//	printf("|NEXT-Type %d,  %s%s%s \n",node->next->type, colors[node->next->type], names[node->next->type], RESET);
	printf("|INDEX %d\n", node->index);
	printf("|--------------------|\n\n");
}

void	print_list_tokens(t_list_of_tok **head)
{
	t_list_of_tok *current = *head;
	while (current != NULL)
	{
		print_node(current);
		current = current->next;
	}
}



