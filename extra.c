/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:08:41 by atucci            #+#    #+#             */
/*   Updated: 2023/12/28 15:14:32 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strchr(char *str, int cherry)
{
	size_t	count;

	count = 0;
	while (str[count])
	{
		if (str[count] == (char)cherry)
			return (&str[count]);
		count++;
	}
	return (NULL);
}

int	my_strcmp(const char *str1, const char *str2)
{
	size_t	count;

	count = 0;
	while (str1[count] != '\0' || str2[count] != '\0')
	{
		if (str1[count] > str2[count])
			return (1);
		else if (str1[count] < str2[count])
			return (-1);
		count++;
	}
	return (0);
}

void	print_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}
