/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:23:17 by atucci            #+#    #+#             */
/*   Updated: 2023/12/30 18:37:52 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

#include <stdio.h>
#include <string.h>

char* find_env_value(char** env, char* dollar)
{
	// Remove $ or ${} from dollar
	char*	key;
	int		i;

	if (dollar[0] == '$')
	{
		if (dollar[1] == '{')
			key = strndup(dollar + 2, strlen(dollar) - 3);
		else
			key = strdup(dollar + 1);
	}
	else
		key = ft_strdup(dollar);
	// Iterate over env
	i = 0;
	while (env[i] != NULL)
	{
		// Check if key is prefix of env[i]
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0 && env[i][ft_strlen(key)] == '=')
		{
			// Return value after =
			free(key);
			return ft_strdup(env[i] + strlen(key) + 1);
		}
		i++;
	}
	return (free(key), NULL);
}

int main(int ac, char** av, char** env)
{
	char	*value;
	if (ac > 1)
	{
		value = find_env_value(env, av[1]);
		if (value != NULL)
		{
			printf("%s\n", value);
			free(value);
		}
		else
			printf("Variable not found in environment\n");
	}
	else
		printf("Usage: %s <variable>\n", av[0]);
	return 0;
}

