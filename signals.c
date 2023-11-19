/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:02:56 by atucci            #+#    #+#             */
/*   Updated: 2023/11/19 15:14:48 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	(void)sig;
		printf("handling signales with ctrl-c\n");
	printf("\n");
}

void	handle_ctrl_d(void)
{
	printf("handling an other signals\n");
}

void	handle_ctrl_backlash(int sig)
{
	(void)sig;
		printf("handling signal with ctrl-boh \n");
}


