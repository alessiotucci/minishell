/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:53:12 by atucci            #+#    #+#             */
/*   Updated: 2024/01/10 10:53:07 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*this function actively look for matches with the wildcards*/
static int	find_matches(char *wildcard, char *name)
{
	char	*prefix;
	char	*suffix;
	char	*asterix;
	char	*copy;

	copy = ft_strdup(wildcard);
	if (copy[0] == '*')
	{
		prefix = NULL;
		suffix = &copy[1];
	}
	else
	{
		asterix = my_strchr(copy, '*');
		if (asterix != NULL)
		{
			*asterix = '\0';
			prefix = copy;
			suffix = asterix + 1;
		}
		else
		{
			// handle the case where there is no '*' in the wildcard
			// for example, you could set prefix and suffix to NULL
			prefix = copy;
			suffix = "";
		}
	}
	if (prefix != NULL && ft_strncmp(name, prefix, ft_strlen(prefix)) != 0)
		return (free(copy),1);
	if (suffix != NULL && my_strcmp(name + ft_strlen(name) - ft_strlen(suffix), suffix) != 0)
		return (free(copy),1);
	return (free(copy),0);

}
/* function to know how many match we find, wildcard = *.txt | ft_* | ft_*.txt */
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

	count = 0;
	max_matrix = count_matches(wildcard); // check for negative -1
	//printf("%sfound %d matches%s\n",BG_RED, max_matrix, BG_RESET);
	if (max_matrix < 1)
		return (perror("no match wildcards"), NULL);
	matrix = malloc(sizeof(char *) * max_matrix + 1); // check for malloc failure
	directory = opendir(".");
	if (directory == NULL)
		return (perror("Error opening directory"), NULL);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (find_matches(wildcard, entry->d_name) == 0)
		{
			//printf("\n%sfound a match! %s %s%s\n",BG_YELLOW, wildcard, entry->d_name, BG_RESET);
			matrix[count] = ft_strdup(entry->d_name);
			count++;
		}
		entry = readdir(directory);
	}
	matrix[count] = NULL; //fixed?
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
			return(1);
		i++;
	}
	return (0);
}

