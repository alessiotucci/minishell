/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:09 by atucci            #+#    #+#             */
/*   Updated: 2024/01/13 16:26:44 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
char	*expansion_dollar(char *dollar, char **env)
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

t_list_of_tok	*node_for_dollar(int lvl, char *spitted, char **env)
{
	char	*expanded;
	char	*dollar_pos = ft_strchr(spitted, '$');
	char	*new_str;
	printf("spitted: %s\n", spitted);
	printf("$ strchr: %s\n", dollar_pos);
	
	if (dollar_pos != NULL && dollar_pos != spitted)
	{
		// Dollar sign is not at the beginning of the string
		// Split the string into two parts: before and after the dollar sign
		char *before_dollar = my_strndup(spitted, dollar_pos - spitted);
		expanded = expansion_dollar(dollar_pos, env);
		if (expanded == NULL)
		{
			printf("I need to handle better these cases\n");
			new_str = ft_strdup(before_dollar);
		}
		else
		{	// FUCK CHECK THE FUNCTION YOU USE!!!
			// Concatenate the part before the dollar sign, the expanded value, and the rest of the string
			new_str = malloc(strlen(before_dollar) + strlen(expanded) + 1);
			strcpy(new_str, before_dollar); // check this
			strcat(new_str, expanded); // check this one too
		}
		free(before_dollar);
	}
	else
	{
		// Dollar sign is at the beginning of the string or not present
		expanded = expansion_dollar(spitted, env);
		if (expanded == NULL)
		{
			printf("I need to handle better these cases\n");
			new_str = ft_strdup("");
		}
		else
			new_str = ft_strdup(expanded);
	}
	
	if (expanded != NULL) {
		free(expanded);
	}
	
	return create_node(lvl, new_str);
}

*/
