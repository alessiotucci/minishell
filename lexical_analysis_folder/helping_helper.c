/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:50:00 by atucci            #+#    #+#             */
/*   Updated: 2023/12/08 21:54:33 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_logical_op(char *str)
{
	if ((my_strcmp(str, "&&") == 0) || (my_strcmp(str, "||") == 0))
		return (1);
	else
		return (0);
}

int	is_dollar(char *str)
{
	if (my_strcmp(str, "$") == 0)
		return (1);
	else
		return (0);
}
