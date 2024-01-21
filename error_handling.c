/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:53:52 by atucci            #+#    #+#             */
/*   Updated: 2024/01/21 13:19:11 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_g_exit(int status)
{
	g_exit_status = status;
}

void	print_and_update(char *str, int status)
{
	set_g_exit(status);
	printf("%s", str);
}
