/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:38:22 by atucci            #+#    #+#             */
/*   Updated: 2023/12/31 18:12:16 by atucci           ###   ########.fr       */
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

char	*find_possible_command(char *command_as_string, char **envp)
{
	int		i;
	int		y;
	char	*possible_command;
	char	**directs;

	directs = find_path_env(envp);
	i = 0;
	while (directs[i] != NULL)
	{
		y = ft_strlen(directs[i]) + ft_strlen(command_as_string) + 2;
		possible_command = malloc(y); // +2 for the '/' and '\0'
		ft_strlcpy(possible_command, directs[i], y);
		ft_strlcat(possible_command, "/", y);
		ft_strlcat(possible_command, command_as_string, y);
		if (access(possible_command, X_OK) == 0)
		{ // Check if the command is executable
			return (possible_command);
		}
		free(possible_command);
		i++;
	}
	return (NULL);
}
/* first handle the redirection
 * then check for builtins
 * otherwise fork and go on with execve
 * */
void	*execute_command(char *command, char **test, char **envp, t_list_of_tok *current)
{
	if (current->file_name != NULL)
		redirection_process(current, current->next->type); // here the fd are changed
	if (current->type == T_BUILTIN)
		return (which_built_in(current));
	else
	{
		if (fork() == 0)
		{
			execve(command, test, envp);
			perror("execve"); // execve returns only on error
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL); // parent waits for the child to finish
	}
return (NULL);
}

/* Function to get the size of the list */
static int get_size(t_list_of_tok *head)
{
	int size = 0;
	while (head != NULL)
	{
		size++;
		head = head->next;
	}
	return size;
}

/* helper function to find the path in the ev */
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



/* Function to create argv for execve */
char **argv_for_exceve(t_list_of_tok **head)
{
	int		size;
	char	**argv;
	int		i;

	size = get_size(*head);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	t_list_of_tok *current = *head;
	i = 0;
	while (current != NULL)
	{
		if (current->type == T_COMMAND || current->type == T_BUILTIN || current->type == T_COMMAND_ARGS || current->type == T_FLAG)
		{
			argv[i] = ft_strdup(current->command_as_string); // duplicate the string
			if (!argv[i])
				return NULL; // return NULL if memory allocation fails
			i++;
		}
		else if (current->type == T_PIPES || current->type == T_REDIR_IN || current->type == T_REDIR_OUT || current->type == T_REDIR_APP || current->type == T_HERE_DOC)
			break;
		current = current->next;
	}
	argv[i] = NULL; // NULL terminate the argv array
	return (argv);
}
