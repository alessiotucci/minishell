/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excevve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:59:54 by atucci            #+#    #+#             */
/*   Updated: 2023/12/24 14:45:55 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <string.h>
#include "../../minishell.h"
#include "../../libft/libft.h"

int main(int ac, char *av[], char **env)
{
	(void) ac;
	(void) av;
	char	*input;
	char	*command;
	char	*path = NULL;
	char	**directs;
	// Find the PATH in the env array
	int i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5; // Skip the "PATH=" part
			break;
		}
	i++;
	}
	//printf("Path: (%s%s%s)\n", GREEN, path, RESET);
	directs = ft_split(path, ':');
	while (1)
	{
		input = readline(RED"miniHell "RESET);
		char **input_parts = ft_split(input, ' ');
		command = NULL;
		i = 0;
		while (directs[i] != NULL)
		{
			char *possible_command = malloc(strlen(directs[i]) + strlen(input_parts[0]) + 2); // +2 for the '/' and '\0'
			strcpy(possible_command, directs[i]);
			strcat(possible_command, "/");
			strcat(possible_command, input_parts[0]);
			if (access(possible_command, X_OK) == 0)// Check if the command is executable
			{
				command = possible_command;
				break;
			}
			free(possible_command);
		i++;
		}
		if (command == NULL)
		{
			printf("Command not found\n");
			free(input);
			free(input_parts);
			continue;
		}
		//char **args = ft_split(command, ' ');
		if (fork() == 0)
		{
			//int execve(const char *path, char *const argv[], char *const envp[])
			//printf("command:[%s]\ninput_parts[0]:%s\nenv[0]:%s\n", command, input_parts[0], env[0]);
			execve(command, input_parts, env);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
		free(input);
		free(command);
		free(input_parts);
	}
	return 0;
}

