/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:13:21 by atucci            #+#    #+#             */
/*   Updated: 2023/11/08 13:43:25 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "built_ins.h"

void	try_builtin()
{
	ft_printf("inside the builtin function folder\n");
	builtin1();
	builtin2();
	builtin3();
	return ;
}
