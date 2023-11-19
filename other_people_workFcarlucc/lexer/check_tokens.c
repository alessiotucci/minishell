/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:11:23 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/11 16:13:54 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parentheses(char *s, int *i)
{
	if (s[*i - 2] == '(' && check_number(s))
		return (1);
	if (is_op(&s[*i - 2]) || is_op(&s[*i - 3]))
	{
		if (!is_op(&s[*i + 2]))
			return (1);
	}
	if (check_number(s))
		return (1);
	return (0);
}

int	check_operator(char *s, int *i)
{
	if ((s[*i] == '|' || s[*i] == '&') && (*i == 0 || *i == 1))
		return (0);
	if (s[*i + 1] == 0 || s[*i + 2] == 0 || is_double(s, i))
		return (0);
	return (1);
}

int	check_quote(char *s)
{
	int		i;
	int		count;
	char	c;

	i = -1;
	count = 0;
	c = 0;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i];
			i++;
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == c)
				count--;
		}
	}
	return (counter(count));
}

int	check_number(char *s)
{
	int		i;
	int		count;
	char	c;

	i = -1;
	count = 0;
	c = 0;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i];
			i++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == '(')
			count++;
		if (s[i] == ')')
			count--;
	}
	return (counter(count));
}
