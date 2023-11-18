/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2023/11/18 11:01:30 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	int		count;
	char	*input;

	count = 1;
	if (ac || av || envp)
		ft_printf("\n");
	while (av[count])
	{
		ft_printf("argoument [%d], %s\t\t", count, av[count]);
		count++;
	}
	while (1)
	{
	lexer();
	token();
	parser();
	try_builtin();
	input = readline("miniHell>");
	if (input != NULL)
	ft_printf("%s\n", input);
	}
}
