/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:30:20 by atucci            #+#    #+#             */
/*   Updated: 2024/01/21 16:36:23 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **my_setenv(char **old_copy, char *key, char *new_value, int append_flag)
{
	int		i;
	char	*new_entry;
	int		key_len;
	char	*old_value;

	key_len = ft_strlen(key);
	i = 0;
	// Look for the key in the old environment
	while (old_copy[i] != NULL)
	{
		if (ft_strncmp(old_copy[i], key, key_len) == 0 && old_copy[i][key_len] == '=')
		{
			// Key found, update the value
			if (append_flag)
			{
				// Append new_value to the existing value
				old_value = old_copy[i] + key_len + 1;
				new_entry = malloc(ft_strlen(old_value) + ft_strlen(new_value) + key_len + 3);
				sprintf(new_entry, "%s=%s%s", key, old_value, new_value);
			}
			else
			{
				// Replace the existing value with new_value
				new_entry = malloc(ft_strlen(new_value) + key_len + 2);
				sprintf(new_entry, "%s=%s", key, new_value);
			}
			free(old_copy[i]);
			old_copy[i] = new_entry;
			return (old_copy);
		}
		i++;
	}
	// Key not found, add a new entry
	old_copy = copy_array(old_copy, 1);
	new_entry = malloc(ft_strlen(new_value) + key_len + 2);
	sprintf(new_entry, "%s=%s", key, new_value);
	old_copy[i] = new_entry;
	return (old_copy);
}

