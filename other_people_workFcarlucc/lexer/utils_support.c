/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:29:55 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/11 16:36:14 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del(void *str)
{
	free(str);
}

char	*create_del(char *s)
{
	char	quote;
	int		i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			while (s[i] && s[i] != quote)
				i++;
			break ;
		}
		i++;
	}
	return (ft_substr(s, 0, i));
}

void	handle_here_doc_sig(int signum)
{
	(void)signum;
	printf("\n");
	exit(130);
}

char	*fix_white_spaces(char *str)
{
	int		i;
	int		j;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (ft_isspace(str[i]) && ft_isspace(str[i + 1]))
			i++;
		else
			res[j++] = str[i++];
	}
	res[j] = 0;
	free(str);
	return (res);
}

int	counter(int count)
{
	if (count != 0)
		return (0);
	return (1);
}
