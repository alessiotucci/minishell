/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2023/12/25 10:39:42 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**find_path_env(char **env)
{
	int	i;
	char *nully = NULL;
	(void)env;
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
	//printf("path env: |%s%s%s|\n",YELLOW, nully, RESET);
	return (ft_split(nully, ':'));
}

t_list_of_tok	*find_command_in_list(t_list_of_tok **head)
{
	t_list_of_tok	*current;

	current = *head;
	while (current != NULL)
	{
		if (current->type == T_COMMAND || current->type == T_BUILTIN)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char *find_pipe_redirect(t_list_of_tok *iterator)
{
	while (iterator != NULL)
	{
		// Check if the current node is a pipe or redirection operator
		if (iterator->type == T_PIPES || iterator->type == T_REDIR_OUT || iterator->type == T_REDIR_APP)
		{
			if (iterator->next == NULL)
			{
				printf("Syntax error: unexpected end of command\n");
				return (NULL);
			}
			//iterator->type = iterator->next->type; Save the type of operator in the current node
			// Save the filename or command in the current node
			iterator->useful_namer = ft_strdup(iterator->next->command_as_string);
			return (iterator->useful_namer);
		}/*
			iterator->next = iterator->next->next;// Skip the next node as we've already processed it
		} */
		iterator = iterator->next;
	}
	return (NULL);
}

/*this function has just being copy and pasted form bing so I need to recheck */
void redirect_output(t_list_of_tok *current)
{
	if (current->useful_namer != NULL)
	{
		int fd = open(current->useful_namer, O_WRONLY | O_CREAT, 0666);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}


void	executor(t_list_of_tok **head, char **envp)
{
	int		i;
	int		y;
	char	**directs;
	char	*command = NULL;
	char	*possible_command;

	t_list_of_tok *current = find_command_in_list(head);
	// I need to check for pipes and redirections
	current->useful_namer = find_pipe_redirect(current);
	printf("FILE TO OPEN | COMMAND TO TAKE: %s%s%s\n", YELLOW, current->useful_namer, RESET);
	if (current == NULL)
	{
		printf("there is no command in the string sadly\n");
		return ;
	}
	i = 0;
	directs = find_path_env(envp);
	while (directs[i] != NULL)
	{
		y = ft_strlen(directs[i]) + ft_strlen(current->command_as_string) + 2;
		possible_command = malloc(ft_strlen(directs[i]) + ft_strlen(current->command_as_string) + 2); // +2 for the '/' and '\0'
		ft_strlcpy(possible_command, directs[i], y);
		ft_strlcat(possible_command, "/", y);
		ft_strlcat(possible_command, current->command_as_string, y);
		if (access(possible_command, X_OK) == 0)// Check if the command is executable
		{
			command = possible_command;
			break;
		}
		free(possible_command);
		i++;
	}
	// I need to create a array of string to pass to the execve!
	char **test = argv_for_exceve(head);
/*                                                                           */
		if (fork() == 0)
		{
			// bing suggest to perform the function call here
			redirect_output(current);
			execve(command, test, envp);
			perror("execve");// execve returns only on error
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);// parent waits for the child to finish
		free(command);
/*                                                                          */
	executor2();
	executor3();
	return ;
}
