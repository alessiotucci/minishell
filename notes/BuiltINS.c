/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuiltINS.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:02:52 by atucci            #+#    #+#             */
/*   Updated: 2024/03/29 19:19:36 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include  "../minishell.h"

# define RED     "\033[1;31m"
# define RESET   "\033[0m"

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
			if (strcmp(array[mount], array[mount + 1]) > 0)
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

//env_copy
char	**copy_array(char **env, int extra_space)
{
	int		env_count;
	char	**env_copy;
	int		i;

	env_count = 0;
	while (env[env_count] != NULL)
		env_count++;
	env_copy = (char **)malloc((env_count + extra_space + 1) * sizeof(char *));
	if (env_copy == NULL)
		return (perror("Error in memory allocation"), NULL);
	i = 0;
	while (env[i] != NULL)
	{
		env_copy[i] = ft_strdup(env[i]);
		if (env_copy[i] == NULL)
			return (perror("Error in memory allocation"), NULL);
		i++;
	}
	while (i < env_count + extra_space)
	{
		env_copy[i] = NULL;
		i++;
	}
	env_copy[env_count + extra_space] = NULL;
	return (env_copy);
}


int	main(int ac, char *av[], char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	printf("This is a test for the builtins ENV, EXPORT, and UNSET\n");
	printf("Creating a copy of ENV\n");
	char **env_copy = copy_array(env, 0);
	printf("Sorting ENV\n");
	sort_string_array(env_copy);
	printf("%s printing the array%s\n***\n\n", RED, RESET);
	print_string_array(env_copy);
	printf("Freeing the copy of ENV\n");
}
