/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:05:47 by atucci            #+#    #+#             */
/*   Updated: 2024/01/13 16:19:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Your provided function
static char *expansion_dollar(char *dollar, char **env)
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
			var_value = expansion_dollar(var_name, env);
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


int main(int argc, char **argv, char **envp)
{
	printf("*** BEFORE ***\n");
	printf("$PWD how are you $USER\n");
	printf("${HOME} this is it\n");
	printf("$PATH$SHELL\n");
	char *str = strdup("$PWD how are you $USER");
	char *str1 = strdup("$HOME this is it");
	char *str2 = strdup("$PATH$SHELL");
	printf("*** after ***\n");
	str = find_and_expand_vars(str, envp);
	str1 = find_and_expand_vars(str1, envp);
	str2 = find_and_expand_vars(str2, envp);
	printf("%s\n", str);
	printf("%s\n", str1);
	printf("%s\n", str2);
//	free(str);
 //   free(str1);
 //   free(str2);
	return 0;
}
