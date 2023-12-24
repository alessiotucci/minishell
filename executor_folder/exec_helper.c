/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:38:22 by atucci            #+#    #+#             */
/*   Updated: 2023/12/24 18:03:50 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	executor1(void)
{
	return ;
}

void	executor2(void)
{
	return ;
}

void	executor3(void)
{
	return ;
}

// Function to get the size of the list
static int get_size(t_list_of_tok *head)
{
	int size = 0;
	while (head != NULL)
	{
		size++;
		head = head->next;
	}
	return size;
}

// Function to create argv for execve
char **argv_for_exceve(t_list_of_tok **head)
{
	int		size;
	char	**argv;
	int		i;

	size = get_size(*head);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		return NULL; // return NULL if memory allocation fails
	t_list_of_tok *current = *head;
	i = 0;
	while (current != NULL)
	{
		// Check if the type of the node is related to a command
		if (current->type == T_COMMAND || current->type == T_BUILTIN || current->type == T_COMMAND_ARGS)
		{
			argv[i] = ft_strdup(current->command_as_string); // duplicate the string
			if (!argv[i])
				return NULL; // return NULL if memory allocation fails
			i++;
		}
		else if (current->type == T_PIPES || current->type == T_REDIR_IN || current->type == T_REDIR_OUT || current->type == T_REDIR_APP || current->type == T_REDIR_DELIMER)
			break;
		current = current->next;
	}
	argv[i] = NULL; // NULL terminate the argv array
	return (argv);
}
