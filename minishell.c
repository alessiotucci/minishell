/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:19 by atucci            #+#    #+#             */
/*   Updated: 2023/11/08 13:40:48 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	ft_printf("checking if makefile works\n");
	if (ac || av || envp)
	ft_printf("ok");
	lexer();
//	token();
	parser();
	try_builtin();
	return (0);
}
