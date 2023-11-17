/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:03:32 by atucci            #+#    #+#             */
/*   Updated: 2023/11/13 15:42:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;
	while (1)
	{
		input = readline("minishelly>");
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
