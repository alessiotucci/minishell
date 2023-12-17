/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excevve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:59:54 by atucci            #+#    #+#             */
/*   Updated: 2023/12/17 17:28:26 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

int main()
{
	char	*input;

	while (1)
	{
		input = readline("Enter command: ");
		char *args[] = {input, NULL};
		char *env_args[] = {"PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin", NULL};
		if (fork() == 0)
		{
			execve(args[0], args, env_args);
			perror("execve");   // execve returns only on error
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);  // parent waits for the child to finish
		free(input);
	}
	return 0;
}

