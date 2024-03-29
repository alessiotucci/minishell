/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:08:41 by atucci            #+#    #+#             */
/*   Updated: 2024/03/26 14:30:40 by atucci           ###   ########.fr       */
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
char	*my_strncpy(char *dst, const char *src, size_t len)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (len > 0)
	{
		if (src_len >= len)
			ft_memcpy(dst, src, len);
		else
		{
			ft_memcpy(dst, src, src_len);
			ft_memset(dst + src_len, '\0', len - src_len);
		}
	}
	return (dst);
}

char	*my_strndup(const char *src_str, size_t max_len)
{
	size_t	str_len;
	char	*dup_str;

	dup_str = malloc(max_len + 1);
	str_len = ft_strlen(src_str);
	if (str_len > max_len)
		str_len = max_len;
	if (!dup_str)
		return (NULL);
	ft_memcpy(dup_str, src_str, str_len);
	dup_str[str_len] = 0;
	return (dup_str);
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
/* helper function to check for null string arrays */
int	check_null_array(char **array)
{
	if (array == NULL)
	{
		printf("%s NULL, SOMETHING IS WRONG%s\n", RED, RESET);
		return (1);
	}
	return (0);
}

void	print_string_array(char **array)
{
	int	i;

	i = 0;
	if (check_null_array(array))
		return ;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	free_string_array(char **array)
{
	int	count;

	count = 0;
	if (check_null_array(array))
		return (1);
	while (array[count])
	{
		free(array[count]);
		count++;
	}
	free(array);
	return (0);
}
/* test */
int	lenght_string_array(char **array)
{
	int	count;
	count = 0;
	if (check_null_array(array))
		return (-1);
	while(array[count] != NULL)
		count++;
	return (count);
}

char	**sort_string_array(char **array)
{
	int		count;
	int		mount;
	int		lenght;
	char	*temp;

	if (check_null_array(array))
		return (NULL);
	count = 0;
	lenght = lenght_string_array(array);
	while (count < lenght - 1)
	{
		mount = 0;
		while (mount < lenght - count - 1)
		{
			if (my_strcmp(array[mount], array[mount + 1]) > 0)
			{
				temp = array[mount];
				array[mount] = array[mount + 1];
				array[mount + 1] = temp;
			}
			mount++;
		}
		count++;
	}
	return (array);
}
