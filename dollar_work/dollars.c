/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:09 by atucci            #+#    #+#             */
/*   Updated: 2024/01/13 18:36:34 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *expansion_dollary(char *dollar, char **env)
{
	char	*key;
	int		i;
	int		key_len;

	if (dollar[0] == '$')
	{
		if (dollar[1] == '{')
			key = strndup(dollar + 2, strlen(dollar) - 3);
		else
			key = strdup(dollar + 1);
	}
	else
		key = strdup(dollar);
	i = 0;
	key_len = strlen(key);
	while (env[i] != NULL)
	{
		if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			free(key);
			return (strdup(env[i] + strlen(key) + 1));
		}
		i++;
	}
	return (free(key), NULL);
}

// Function to replace a substring with another string
char *replace_substr(char *str, char *substr, char *replacement)
{
	char *result;
	char *ins;
	char *tmp;
	int len_sub;
	int len_rep;
	int len_front;
	int count;

	count = 0;
	len_sub = strlen(substr);
	if (!str || !substr || len_sub == 0)
		return NULL;
	if (!replacement)
		replacement = "";
	len_rep = strlen(replacement);
	ins = str;
	tmp = strstr(ins, substr);
	while (tmp != NULL)
	{
		count++;
		ins = tmp + len_sub;
		tmp = strstr(ins, substr);
	}	
	tmp = result = malloc(strlen(str) + (len_rep - len_sub) * count + 1);
	if (!result)
		return NULL;
	while (count--)
	{
		ins = strstr(str, substr);
		len_front = ins - str;
		tmp = strncpy(tmp, str, len_front) + len_front;
		tmp = strcpy(tmp, replacement) + len_rep;
		str += len_front + len_sub;
	}
	strcpy(tmp, str);
	return result;
}

char *find_and_expand_vars(char *str, char **env)
{
	int		i;
	char	*var_start;
	char	*var_end;
	char	*var_name;
	char	*var_value;
	char	*var_name_with_dollar;
	char	*new_str;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			var_start = str + i + 1;
			var_end = var_start;
			while (*var_end != '\0' && *var_end != ' ' && *var_end != '$')
				var_end++;
			var_name = strndup(var_start, var_end - var_start);
			var_value = expansion_dollary(var_name, env);
			if (var_value != NULL)
			{
				var_name_with_dollar = malloc(strlen(var_name) + 2); // +2 for the dollar sign and null terminator
				var_name_with_dollar[0] = '$';
				strcpy(var_name_with_dollar + 1, var_name);
				new_str = replace_substr(str, var_name_with_dollar, var_value);
				free(var_name_with_dollar);
				free(str);
				str = new_str;
				free(var_value);
			}
			free(var_name);
		}
	i++;
	}
	return str;
}


