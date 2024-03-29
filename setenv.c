/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:30:20 by atucci            #+#    #+#             */
/*   Updated: 2024/03/26 16:28:54 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	my_sprintf(char *buffer, char *key, char *old_value, char *new_value)
{
	int	bufflen;

	bufflen = ft_strlen(buffer);
	ft_strlcpy(buffer, key, ft_strlen(key) + 1);
	ft_strlcat(buffer, "=", bufflen + 2);
	if (old_value != NULL)
		ft_strlcat(buffer, old_value, ft_strlen(old_value) + bufflen + 1);
	ft_strlcat(buffer, new_value, ft_strlen(new_value) + bufflen + 1);
}


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
		if (ft_strncmp(old_copy[i], key, key_len) == 0
			&& old_copy[i][key_len] == '=')
		{
			// Key found, update the value
			if (append_flag)
			{
				// Append new_value to the existing value
				old_value = old_copy[i] + key_len + 1;
				new_entry = malloc(ft_strlen(old_value) + ft_strlen(new_value) + key_len + 3);
				//sprintf(new_entry, "%s=%s%s", key, old_value, new_value);
				my_sprintf(new_entry, key, old_value, new_value);
			}
			else
			{
				// Replace the existing value with new_value
				new_entry = malloc(ft_strlen(new_value) + key_len + 2);
				//sprintf(new_entry, "%s=%s", key, new_value);
				my_sprintf(new_entry, key, NULL, new_value);
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
	//sprintf(new_entry, "%s=%s", key, new_value);
	my_sprintf(new_entry, key, NULL, new_value);
	old_copy[i] = new_entry;
	return (old_copy);
}

#include <string.h>

char	*new_entry_func(char *key, char *old_vue, char *new_vue, int flag)
{
	char	*new_entry;
	int		key_len = ft_strlen(key);
	int		old_vue_len = ft_strlen(old_vue);
	int		new_vue_len = ft_strlen(new_vue);

	if (flag)
	{
		new_entry = malloc(old_vue_len + new_vue_len + key_len + 3);
		ft_strlcpy(new_entry, key, key_len +1);
		ft_strlcat(new_entry, "=", 2);
		ft_strlcat(new_entry, old_vue, old_vue_len + 1);
		ft_strlcat(new_entry, new_vue, new_vue_len + 1);
	}
	else
	{
		new_entry = malloc(new_vue_len + key_len + 2);
		ft_strlcpy(new_entry, key, key_len + 1);
		ft_strlcat(new_entry, "=", 2);
		ft_strlcat(new_entry, new_vue, new_vue_len + 1);
	}

	return new_entry;
}

char **my_setenv1(char **old_copy, char *key, char *new_value, int append_flag)
{
	int		i;
	char	*new_entry;
	int		key_len;
	char	*old_value;

	key_len = strlen(key);
	i = 0;
	// Look for the key in the old environment
	while (old_copy[i] != NULL)
	{
		if (strncmp(old_copy[i], key, key_len) == 0
			&& old_copy[i][key_len] == '=')
		{
			// Key found, update the value
			old_value = old_copy[i] + key_len + 1;
			new_entry = new_entry_func(key, old_value, new_value, append_flag);
			free(old_copy[i]);
			old_copy[i] = new_entry;
			return (old_copy);
		}
		i++;
	}
	// Key not found, add a new entry
	old_copy = copy_array(old_copy, 1);
	new_entry = new_entry_func(key, NULL, new_value, 0);
	old_copy[i] = new_entry;
	return (old_copy);
}

