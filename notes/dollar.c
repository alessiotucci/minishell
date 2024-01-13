/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:23:17 by atucci            #+#    #+#             */
/*   Updated: 2024/01/13 16:24:16 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

#include <stdio.h>
#include <strind.h>

char	*find_env_value(char **env, char *dollar)
{
	char	*key;
	int		i;
	int		key_len;

	if (dollar[0] == '$')
	{
		if (dollar[1] == '{')
			key = my_strndup(dollar + 2, ft_strlen(dollar) - 3);
		else
			key = ft_strdup(dollar + 1);
	}
	else
		key = ft_strdup(dollar);
	i = 0;
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			free(key);
			return (ft_strdup(env[i] + ft_strlen(key) + 1));
		}
		i++;
	}
	return (free(key), NULL);
}

int	main(int ac, char **av, char **env)
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
	return (0);
}
