/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2023/12/04 12:35:21 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c); 
	signal(SIGQUIT, handle_ctrl_backlash); 
}

int	main(int ac, char *av[], char *envp[])
{
	int		count;
	char	*input;

	count = 1;
	if (ac || av || envp)
		ft_printf("\n");
	while (1)
	{
	handle_signal();
	input = readline("minishell% ");
	if (lexer(input) == 1)
		return (1);// what we need to return for syntax error? 
	//	token();
//	parser();
//	try_builtin();
	if (input != NULL)
	ft_printf("%s\n", input);
	}
}
