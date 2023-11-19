/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:15:57 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/11 17:45:26 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_syntax(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i + 1] && ((str[i] == '|' && str[i + 1] == '|') \
		|| (str[i] == '&' && str[i + 1] == '&') \
		|| (str[i] == '<' && str[i + 1] == '<') \
		|| (str[i] == '>' && str[i + 1] == '>')))
			count += 2;
		else if (ft_strchr("|()<>", str[i]))
			count += 2;
		i++;
	}
	return (i + count);
}

char	*fix_syntax(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(count_syntax(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			res = handle_quotes(str, res, &i, &j);
		else if (str[i + 1] && is_two_char(&str[i]))
			res = handle_two(str, res, &i, &j);
		else if (ft_strchr("|()<>", str[i]))
			res = handle_one(str, res, &i, &j);
		else
			res[j++] = str[i++];
	}
	res[j] = 0;
	res = fix_white_spaces(res);
	return (res);
}

char	*handle_quotes(char *str, char *res, int *i, int *j)
{
	char	c;

	c = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		c = str[*i];
		res[(*j)++] = str[(*i)++];
		while (str[*i] && str[*i] != c)
			res[(*j)++] = str[(*i)++];
		if (str[*i] == c)
			res[(*j)++] = str[(*i)++];
	}
	return (res);
}

char	*handle_two(char *str, char *res, int *i, int *j)
{
	if ((*i != 0 && str[*i - 1] != ' ') && (str[*i + 2] && str[*i + 2] != ' '))
	{
		res[(*j)++] = ' ';
		res[(*j)++] = str[(*i)++];
		res[(*j)++] = str[(*i)++];
		res[(*j)++] = ' ';
	}
	else if (*i != 0 && str[*i - 1] != ' ')
	{
		res[(*j)++] = ' ';
		res[(*j)++] = str[(*i)++];
		res[(*j)++] = str[(*i)++];
	}
	else
	{
		res[(*j)++] = str[(*i)++];
		res[(*j)++] = str[(*i)++];
		res[(*j)++] = ' ';
	}
	return (res);
}

char	*handle_one(char *str, char *res, int *i, int *j)
{
	if ((*i != 0 && str[*i - 1] != ' ') && (str[*i + 1] && str[*i + 1] != ' '))
	{
		res[(*j)++] = ' ';
		res[(*j)++] = str[(*i)++];
		res[(*j)++] = ' ';
	}
	else if (*i != 0 && str[*i - 1] != ' ')
	{
		res[(*j)++] = ' ';
		res[(*j)++] = str[(*i)++];
	}
	else
	{
		res[(*j)++] = str[(*i)++];
		res[(*j)++] = ' ';
	}
	return (res);
}
