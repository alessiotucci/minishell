/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:46 by atucci            #+#    #+#             */
/*   Updated: 2024/01/05 15:57:36 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*5) helper function for this case */
static char	*expansion_dollar(char *dollar, char **env)
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

/*4) 
 * This function takes a node and a strings, performs several check 
 * then create the node with the fields initialized if needed, we will go 
 * from there with further implementation
*/
static t_list_of_tok	*node_for_dollar(int lvl, char *spitted, char **env)
{
	char	*expanded;

	expanded = expansion_dollar(spitted, env);
	if (expanded == NULL)
	{
		printf("I need to handle better these cases\n");
		return (create_node(lvl, "failure"));
	}
	else
		return (create_node(lvl, expanded));
}

/*3) Helper function to expand the wildcard  */
static t_list_of_tok	*node_for_wildcard(int level, char *spitted_cmd)
{
	char			**expanded;
	int				i;
	t_list_of_tok	*current;
	t_list_of_tok	*new_node;
	t_list_of_tok	*head;

	head = NULL;
	i = 0;
	expanded = expansion_wildcard(spitted_cmd);
	if (expanded == NULL)
	{
		printf("I need to handle better these cases\n");
		return (create_node(level, "failure"));
	}
	while (expanded[i])
	{
		new_node = create_node(level, expanded[i]);
		if (head == NULL)
			head = new_node;
		else
		{
			current = head;
			while (current->next != NULL)
				current = current->next;
			current->next = new_node;
			new_node->previous = current;
			new_node->index = current->index + 1;
		}
		i++;
	}
	return (head);
}

/*2)  Helper function to create a new node */
t_list_of_tok	*create_node(int level, char *spitted_cmd)
{
	t_list_of_tok	*new_node;

	new_node = (t_list_of_tok *)malloc(sizeof(t_list_of_tok));
	if (new_node == NULL)
	{
		printf("Error with malloc");
		exit(1);
	}
	new_node->token = spitted_cmd;
	new_node->type = type_of_token(spitted_cmd);
	new_node->priority_lev = level;
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->index = 0;
	new_node->fd_pipe_in = STDIN_FILENO;
	new_node->fd_pipe_out = STDOUT_FILENO; // this is the latest updated here
	return (new_node);
}

/*1) Function to create a list of tokens */
t_list_of_tok	*create_list_of_tok(t_list_of_tok **head, char *cmd, char **env)
{
	t_list_of_tok	*new_node;
	t_list_of_tok	*current;

	if (valid_wildcard(cmd))
		new_node = node_for_wildcard(0, cmd);
	else if (cmd[0] == '$')
		new_node = node_for_dollar(0, cmd, env);
	else
		new_node = create_node(0, cmd);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
		new_node->index = current->index + 1;
	}
	return (new_node);
}
