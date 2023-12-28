/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:53:12 by atucci            #+#    #+#             */
/*   Updated: 2023/12/28 16:36:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*this function actively look for matches with the wildcards*/
static int	find_matches(char *wildcard, char *name)
{
	char	*prefix;
	char	*suffix;
	char	*asterix;
	if (wildcard[0] == '*')
	{
		prefix = NULL;
		suffix = &wildcard[1];
	}
	else if (wildcard[ft_strlen(wildcard) - 1] == '*')
	{
		suffix = NULL;
		wildcard[ft_strlen(wildcard) -1] = '\0';
		prefix = wildcard;
	}
	else
	{
		asterix = my_strchr(wildcard, '*');
		*asterix = '\0';
		prefix = wildcard;
		suffix = asterix + 1;
	}
	if (prefix != NULL && ft_strncmp(name, prefix, ft_strlen(prefix)) != 0)
		return (1);
	if (suffix != NULL && my_strcmp(name + ft_strlen(name) - ft_strlen(suffix), suffix) != 0)
		return (1);
	return (0);
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
	printf("counting matches,WILDCARD:%s\n", wildcard);
	entry = readdir(directory);
	while (entry != NULL)
	{
		printf("%ssegvault coming%s, count check: [%d]\n", RED, RESET, count);
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
	printf("expanision of wildcard, %s\n", wildcard);
	count = 0;
	max_matrix = count_matches(wildcard); // check for negative -1
	printf("found %d matches\n", max_matrix);
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
			printf("\nfound a match between %s, and %s\n", wildcard, entry->d_name);
			matrix[count] = ft_strdup(entry->d_name);
			count++;
		}
		entry = readdir(directory);
	}
	matrix[count] = NULL; //fixed?
	if (closedir(directory) == -1)
		return (perror("Error closing directory"), NULL);
	return (matrix);
}
/* this function check wheter a wildcard is valid or not */
int	valid_wildcard(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return(printf("%sis valid wildcard\n%s", GREEN, RESET));
		i++;
	}
	return (0);
}

