/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:53:12 by atucci            #+#    #+#             */
/*   Updated: 2024/01/10 11:05:28 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*this function actively look for matches with the wildcards*/
static int	find_matches(char *wildcard, char *nam)
{
	char	*prefix;
	char	*sufx;
	char	*asterix;
	char	*copy;

	copy = ft_strdup(wildcard);
	if (copy[0] == '*')
	{
		prefix = NULL;
		sufx = &copy[1];
	}
	else
	{
		asterix = my_strchr(copy, '*');
		if (asterix != NULL)
		{
			*asterix = '\0';
			prefix = copy;
			sufx = asterix + 1;
		}
		else
		{
			prefix = copy;
			sufx = "";
		}
	}
	if (prefix != NULL && ft_strncmp(nam, prefix, ft_strlen(prefix)) != 0)
		return (free(copy), 1);
	if (sufx != NULL && my_strcmp(nam + ft_strlen(nam) - ft_strlen(sufx), sufx) != 0)
		return (free(copy), 1);
	return (free(copy),0);
}

/* function to know how many match we find,
 * wildcard = *.txt | ft_* | ft_*.txt */
static int	count_matches(char *wildcard)
{
	DIR				*directory;
	struct dirent	*entry;
	int				count;

	directory = opendir(".");
	if (directory == NULL)
		return (perror("Error opening directory"), -1);
	count = 0;
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (find_matches(wildcard, entry->d_name) == 0)
			count++;
		entry = readdir(directory);
	}
	if (closedir(directory) == -1)
		return (perror("Error closing directory"), -1);
	return (count);
}

/* Helper function to expland wildcard and create a node for each */
char	**expansion_wildcard(char *wildcard)
{
	DIR				*directory;
	struct dirent	*entry;
	char			**matrix;
	int				max_matrix;
	int				count;

	count = 0;
	max_matrix = count_matches(wildcard);
	if (max_matrix < 1)
		return (perror("no match wildcards"), NULL);
	matrix = malloc(sizeof(char *) * max_matrix + 1);
	directory = opendir(".");
	if (directory == NULL)
		return (perror("Error opening directory"), NULL);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (find_matches(wildcard, entry->d_name) == 0)
		{
			matrix[count] = ft_strdup(entry->d_name);
			count++;
		}
		entry = readdir(directory);
	}
	matrix[count] = NULL;
	if (closedir(directory) == -1)
		return (perror("Error closing directory"), NULL);
	return (sort_string_array(matrix));
}

/* this function check wheter a wildcard is valid or not */
int	valid_wildcard(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
