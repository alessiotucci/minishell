/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:53:12 by atucci            #+#    #+#             */
/*   Updated: 2023/12/28 12:52:54 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_matches(char *wildcard, char *name)
{
	int		name_len;
	int		wildcard_len;
	char	*suffix;
	char	*prefix;
	int		suffix_len;
	int		prefix_len;
	int		result;

	wildcard_len = ft_strlen(wildcard);
	name_len = ft_strlen(name);
	if (wildcard[0] == '*')
	{
		suffix = wildcard + 1; // skip the '*'
		suffix_len = wildcard_len - 1;
		if (suffix_len > name_len)
			return (-1); // name is too short to match the suffix
		return my_strcmp(name + name_len - suffix_len, suffix);
	}
	else// if (wildcard[wildcard_len - 1] == '*')
	{
		prefix = strndup(wildcard, wildcard_len - 1); // copy the string without the '*'
		prefix_len = wildcard_len - 1;
		if (prefix_len > name_len)
			return(free(prefix), -1);
		result = ft_strncmp(name, prefix, prefix_len);
		return (free(prefix),result);
	}
}

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
		if (find_matches(wildcard, entry->d_name) == 0) // match found
			count++;
		entry = readdir(directory);
	}
	if (closedir(directory) == -1)
		return (perror("Error closing directory"), -1);
	return count;
}

/* Helper function to expland wildcard and create a node for each */
char	**expansion_wildcard(char *wildcard)
{
	DIR				*directory;
	struct dirent	*entry;
	char			**matrix;
	int				max_matrix;
	int				count;
	printf("expanision of wildcard\n");
	count = 0;
	max_matrix = count_matches(wildcard); // check for negative -1
	if (max_matrix < 1)
		return (perror("no match wildcards"), NULL);
	matrix = malloc(sizeof(char *) * max_matrix); // check for malloc failure
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
	if (closedir(directory) == -1)
		return (perror("Error closing directory"), NULL);
	return (matrix);
}
/* this function check wheter a wildcard is valid or not */
int	valid_wildcard(const char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == '*' || str[len - 1] == '*')
		return(printf("%sis valid wildcard\n%s", GREEN, RESET));
	else
		return (0);
}

