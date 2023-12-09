/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parethesis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:29:51 by atucci            #+#    #+#             */
/*   Updated: 2023/12/09 19:41:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_spaces_around_parentheses(char *command)
{
	int		length;
	char	*new_command;
	int		i;
	int		j;

	i = 0;
	j = 0;
	length = strlen(command);
	new_command = malloc(length * 2 + 1);
	while (command[i] != '\0')
	{
		if (command[i] == '(' || command[i] == ')')
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
