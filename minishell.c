/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2023/11/09 11:45:43 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	int	count;

	count = 1;
	if (ac || av || envp)
		ft_printf("lets start");
	while (av[count])
	{
		ft_printf("argoument [%d], %s\t\t", count, av[count]);
		count++;
	}
	lexer();
	token();
	parser();
	try_builtin();
	return (0);
}
