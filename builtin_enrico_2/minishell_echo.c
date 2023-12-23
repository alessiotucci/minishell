/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:21:00 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/23 16:23:17 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void minishell_echo(char *args[])
{
	int i = 1;
	int suppress_newline = 0;

	// Check for the -n option
	if (args[1] != NULL && strcmp(args[1], "-n") == 0)
	{
		suppress_newline = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		// Print space between arguments
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	// Print newline unless -n option is used
	if (!suppress_newline)
		printf("\n");
}

int main() {
	char *args[] = { "echo", "-n", "Hello", "World", NULL };
	minishell_echo(args);
	return 0;
}
