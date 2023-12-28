/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:53:12 by atucci            #+#    #+#             */
/*   Updated: 2023/12/28 08:55:57 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* this function check wheter a wildcard is valid or not */
int	valid_wildcard(const char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == '*' || str[len - 1] == '*')
		return(printf("%sis valid wildcard\n%s", GREEN, RESET));
	else
		return (0);
}

