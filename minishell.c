/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2024/01/01 13:14:32 by atucci           ###   ########.fr       */
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
//	int		count;
	char	*input;

//	count = 1;
	if (ac || av || envp)
		ft_printf("\n");
	while (1)
	{
		handle_signal();
		input = readline(RED"minishell% "RESET);
		add_history(input);
		if (input == NULL)
			return (0 * write(1, "\n", 1));
		if (input != NULL && lexer(input, envp) == 1)
			return (1);
	// what we need to return for syntax error? 
	//	token();
	//	parser();
	//	try_builtin();
	}
}
