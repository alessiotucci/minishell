/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:03:32 by atucci            #+#    #+#             */
/*   Updated: 2024/01/09 17:04:28 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

void minishellExit(int exitCode);

// commenzo
int	main(void)
{
	char	*input;
	
	while (1)
	{
		input = readline("minishelly>");
		 // Verifica se l'utente ha inserito "exit" come comando
        if (strcmp(input, "exit") == 0)
        {
            // Chiamata alla tua funzione di uscita personalizzata
            minishellExit(0);
        }
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
