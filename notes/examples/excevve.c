/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excevve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:59:54 by atucci            #+#    #+#             */
/*   Updated: 2023/12/23 12:37:33 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <string.h>
#include "../../minishell.h"

int main(int ac, char *av[], char **env)
{
	(void) ac;
	(void) av;
	char	*input;
	char	*command;

	while (1)
	{
		input = readline(RED"miniHell "RESET);
		command = malloc(strlen("/bin/") + strlen(input) + 1);  // allocate memory for the command
		strcpy(command, "/bin/");// copy "/bin/" to command
		strcat(command, input);// append input to command
		char *args[] = {command, NULL};
		if (fork() == 0)
		{
			execve(command, args, env);
			perror("execve");// execve returns only on error
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);// parent waits for the child to finish
		free(input);
		free(command);
	}
	return 0;
}

