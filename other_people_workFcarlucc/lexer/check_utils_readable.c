/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils_readable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:08:41 by atucci            #+#    #+#             */
/*   Updated: 2023/11/19 17:27:59 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* The is_operation function checks if the string str is an operator.
It returns (-1) if str is a single pipe '|' or a double pipe '||' 
or double ampersand '&&'.
It returns (1) if str starts with a double pipe '||', double ampersand '&&',
or a single pipe followed by a space '| '. It returns (0) otherwise.
*/

int	is_operation(char *str)
{
	if (my_strcmp(str, "|") == 0)
		return (-1);
	if (my_strcmp(str, "||") == 0 || my_strcmp(str, "&&") == 0)
		return (-1);
	if (ft_strncmp(str, "||", 2) == 0
		|| ft_strncmp(str, "&&", 2) == 0
		|| str[0] == '|')
		return (1);
	return (0);
}

/*The is_redirection function checks if the str is a redirection operator.
It returns (-1) if str is a single '<' or '>' or a double '<<' or '>>'.
It returns (1) if str starts with a double '<<' or '>>', or a single '<' or '>'
followed by a space.
It returns (0) otherwise.
 */
int	is_redirection(char *str)
{
	if (my_strcmp(str, "<") == 0 || my_strcmp(str, ">") == 0)
		return (-1);
	if (my_strcmp(str, "<<") == 0 || my_strcmp(str, ">>") == 0)
		return (-1);
	if (ft_strncmp(str, "<<", 2) == 0
		|| ft_strncmp(str, ">>", 2) == 0
		|| str[0] == '<'
		|| str[0] == '>')
		return (1);
	return (0);
}

/* The is_single_char_operator function checks if the string str starts with a 
single operator or redirection character followed by a space.
 * It returns (1) if str starts with '| ', '& ', '< ', or '> '.
 * It returns (0) otherwise.
 */
int	is_single_char_operator(char *str)
{
	if (str[1] == ' '
		&& (str[0] == '|'
			|| str[0] == '&'
			|| str[0] == '<'
			|| str[0] == '>'))
		return (1);
	return (0);
}

/*The is_double_char_operator function checks if the string 
starts with a double 
operator or redirection character.
It returns (1) if str starts with '||', '&&', '<<', or '>>'.
It returns (0) otherwise.
 */
int	is_double_char_operator(char *str)
{
	if (ft_strncmp(str, "||", 2) == 0
		|| ft_strncmp(str, "&&", 2) == 0
		|| ft_strncmp(str, "<<", 2) == 0
		|| ft_strncmp(str, ">>", 2) == 0)
		return (1);
	return (0);
}