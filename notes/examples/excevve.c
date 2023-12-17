/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excevve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:59:54 by atucci            #+#    #+#             */
/*   Updated: 2023/12/17 18:18:09 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

int main(int ac, char *av[], char **env)
{
	(void) ac;
	(void) av;
	char	*input;

	while (1)
	{
		input = readline("Enter command: ");
		char *args[] = {input, NULL};
		if (fork() == 0)
		{
			execve("/bin/ls", args, env);
			perror("execve");   // execve returns only on error
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);  // parent waits for the child to finish
		free(input);
	}
	return 0;
}

