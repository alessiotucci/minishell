/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:38:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/14 16:59:47 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	executor1(void)
{
	return ;
}

void	executor2(void)
{
	return ;
}

void	executor3(void)
{
	return ;
}

/* 4) */
char	*find_path_command(char *token, char **envp)
{
	int		i;
	int		y;
	char	*possible_command;
	char	**directs;

	directs = find_path_env(envp);
	i = 0;
	while (directs[i] != NULL)
	{
		y = ft_strlen(directs[i]) + ft_strlen(token) + 2;
		possible_command = malloc(y);
		ft_strlcpy(possible_command, directs[i], y);
		ft_strlcat(possible_command, "/", y);
		ft_strlcat(possible_command, token, y);
		if (access(possible_command, X_OK) == 0)
			return (possible_command);
		free(possible_command);
		i++;
	}
	return (NULL);
}

/*3) Function to get the size of the list */
static int	get_size(t_list_of_tok *head)
{
	int	size;

	size = 0;
	while (head != NULL)
	{
		size++;
		head = head->next;
	}
	return (size);
}

/*2) helper function to find the path in the ev */
char	**find_path_env(char **env)
{
	int		i;
	char	*nully;

	nully = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			nully = env[i] + 5;
			break ;
		}
		i++;
	}
	return (ft_split(nully, ':'));
}

/*1) Function to create argv for execve */
char	**array_from_list(t_list_of_tok **head)
{
	int				size;
	char			**argv;
	t_list_of_tok	*current;
	int				i;

	size = get_size(*head);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	current = *head;
	i = 0;
	while (current != NULL)
	{
		if (current->type == T_COMMAND || current->type == T_BUILTIN || current->type == T_COMMAND_ARGS || current->type == T_FLAG)
		{
			argv[i] = ft_strdup(current->token);
			if (!argv[i])
				return (NULL);
			i++;
		}
		else if (current->type == T_PIPES || current->type == T_REDIR_IN || current->type == T_REDIR_OUT || current->type == T_REDIR_APP || current->type == T_HERE_DOC)
			break ;
		current = current->next;
	}
	argv[i] = (NULL);
	return (argv);
}
