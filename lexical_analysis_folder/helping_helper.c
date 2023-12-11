/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:50:00 by atucci            #+#    #+#             */
/*   Updated: 2023/12/11 10:16:21 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "stdbool.h"

char	*replace_me(char *str, char quote, char replacement, char me)
{
	int		i;
	bool	inside_quote;

	i = 0;
	inside_quote = false;
	while (str[i])
	{
		if (str[i] == quote)
		{
			inside_quote = !inside_quote;
			i++;
		}
		if (inside_quote && str[i] == me)
			str[i] = replacement;
		i++;
	}
	return (str);
}

int	is_logical_op(char *str)
{
	if ((my_strcmp(str, "&&") == 0) || (my_strcmp(str, "||") == 0))
		return (1);
	else
		return (0);
}

int	is_flag(char *str)
{
	if (str[0] == '-')
		return (1);
	else
		return (0);
}

int	is_dollar(char *str)
{
	if (my_strcmp(str, "$") == 0)
		return (1);
	else
		return (0);
}

int	is_builtin(char *str)
{
	if (my_strcmp(str, "echo") == 0
		|| my_strcmp(str, "cd") == 0
		|| my_strcmp(str, "pwd") == 0
		|| my_strcmp(str, "export") == 0
		|| my_strcmp(str, "unset") == 0
		|| my_strcmp(str, "env") == 0)
		|| my_strcmp(str, "exit") == 0
		return (1);
	else
		return (0);
}
