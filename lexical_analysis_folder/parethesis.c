/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parethesis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:29:51 by atucci            #+#    #+#             */
/*   Updated: 2023/12/21 12:31:01 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parentheses(char* str)
{
	int count = 0;
	while (*str != '\0')
	{
	if (*str == '(')
	{
		count++;
	}
	else if (*str == ')')
	{
		if (count == 0)
		{
			return (-1); // unbalanced
		}
		count--;
	}
		str++;
	}
	if (count == 0)
		return (0);
	else
		return (-1);
	// return count == 0 ? 0 : -1; // 0 if balanced
}
/*this function will be used to assign priority inside the parenthesis*/
void	priority_level(t_list_of_tok **head)
{
	t_list_of_tok	*current;
	int				priority;

	priority = 0;
	current = *head;
	while (current != NULL)
	{
		if (my_strcmp(current->command_as_string, "(") == 0)
			priority++;
		else if (my_strcmp(current->command_as_string, ")") == 0)
			priority--;
		current->priority_lev = priority;
		current = current->next;
	}
	return ;
}

char	*add_spaces_around_symbols(char *command)
{
	int		length;
	char	*new_command;
	int		i;
	int		j;

	i = 0;
	j = 0;
	length = ft_strlen(command);
	new_command = malloc(length * 2 + 1);
	while (command[i] != '\0')
	{
		if ((command[i] == '>' && command[i + 1] == '>') || (command[i] == '<' && command[i + 1] == '<'))
		{
			new_command[j++] = ' ';
			new_command[j++] = command[i];
			new_command[j++] = command[i + 1];
			new_command[j++] = ' ';
			i++;
		}
		else if (command[i] == '(' || command[i] == ')' || command[i] == '>' || command[i] == '<')
		{
			new_command[j++] = ' ';
			new_command[j++] = command[i];
			new_command[j++] = ' ';
		}
		else
			new_command[j++] = command[i];
		i++;
	}
	new_command[j] = '\0';
	return (new_command);
}
