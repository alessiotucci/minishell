/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2023/11/18 13:01:04 by atucci           ###   ########.fr       */
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
	while (1)
	{
	input = readline("miniHell>");
	lexer(input);
//	token();
//	parser();
//	try_builtin();
	if (input != NULL)
	ft_printf("%s\n", input);
	}
}
