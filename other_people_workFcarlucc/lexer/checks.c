/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:08:28 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/11 17:17:53 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '(')
		{
			if (!check_parentheses(s, &i))
				return (0);
		}
		else if (s[i] == ')' && (s[i + 2] != 0))
		{
			i += 2;
			if (!is_op_or_red(s, &i))
				return (0);
			i -= 2;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			if (!check_quote(s))
				return (0);
		}
		else if (is_op_or_red(s, &i))
		{
			if (!check_operator(s, &i) || is_op_or_red(s, &i) < 0)
				return (0);
			// else if (s[i] == '<' && s[i + 1] == '<' && s[i + 3])
			// {
			// 	handle_here_doc(create_del(&s[i + 3]), mini);
			// 	if (g_last_exit_status_cmd == 130)
			// 		return (0);
			// }
		}
	}
	return (1);
}

int	checks(char *s, int *i)
{
	if (s[*i] == '\'' || s[*i] == '"')
	{
		if (!check_quote(s))
			return (0);
	}
	else if (is_op_or_red(s, i))
	{
		if (!check_operator(s, i) || is_op_or_red(s, i) < 0)
			return (0);
		// else if (s[*i] == '<' && s[*i + 1] == '<' && s[*i + 3])
		// {
		// 	handle_here_doc(create_del(&s[*i + 3]), mini);
		// 	if (g_last_exit_status_cmd == 130)
		// 		return (0);
		// }
	}
	return (1);
}

int	is_op_or_red(char *s, int *i)
{
	if (is_op(&s[*i]) || is_red(&s[*i]))
		return (1);
	if (is_op(&s[*i]) < 0 || is_red(&s[*i]) < 0)
		return (-1);
	return (0);
}

int	is_double(char *s, int *i)
{
	if (is_op(&s[*i]) && is_one_char(&s[*i]))
		if (is_op(&s[*i + 2]))
			return (1);
	if (is_op(&s[*i]) && is_two_char(&s[*i]))
		if (is_op(&s[*i + 3]))
			return (1);
	if (is_red(&s[*i]) && is_one_char(&s[*i]))
		if (is_red(&s[*i + 2]) || is_op(&s[*i + 2]))
			return (1);
	if (is_red(&s[*i]) && is_two_char(&s[*i]))
		if (is_red(&s[*i + 3]) || is_op(&s[*i + 3]))
			return (1);
	return (0);
}
