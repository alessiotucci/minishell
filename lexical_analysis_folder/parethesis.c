/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parethesis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:29:51 by atucci            #+#    #+#             */
/*   Updated: 2024/01/24 17:17:23 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parentheses(char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '(')
			count++;
		else if (*str == ')')
		{
			if (count == 0)
				return (-1);
			count--;
		}
		str++;
	}
	if (count == 0)
		return (0);
	else
		return (-1);
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
		if (my_strcmp(current->token, "(") == 0)
			priority++;
		else if (my_strcmp(current->token, ")") == 0)
			priority--;
		current->priority_lev = priority;
		current = current->next;
	}
	return ;
}

char	*add_spaces_around_symbols(char *cmd)
{
	int		length;
	char	*new_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	length = ft_strlen(cmd);
	new_cmd = malloc(length * 2 + 1);
	while (cmd[i] != '\0')
	{
		if ((cmd[i] == '>' && cmd[i + 1] == '>')
			|| (cmd[i] == '<' && cmd[i + 1] == '<'))
		{
			new_cmd[j++] = ' ';
			new_cmd[j++] = cmd[i];
			new_cmd[j++] = cmd[i + 1];
			new_cmd[j++] = ' ';
			i++;
		}
		else if (cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '>' || cmd[i] == '<')
		{
			new_cmd[j++] = ' ';
			new_cmd[j++] = cmd[i];
			new_cmd[j++] = ' ';
		}
		else
			new_cmd[j++] = cmd[i];
		i++;
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}
