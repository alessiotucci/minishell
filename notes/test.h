/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:08:13 by atucci            #+#    #+#             */
/*   Updated: 2023/11/11 15:30:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum s_token_type
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	INPUT_REDIRECTION,
	OUTPUT_REDIRECTION,
	HERE_DOCUMENT,
	OUTPUT_REDIRECTION_APPEND,
	PIPE,
	ENV_VAR,
	EXIT_STATUS,
	CTRL_C,
	CTRL_D,
	CTRL_BACKSLASH,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	LOGICAL_AND,
	LOGICAL_OR,
	WILDCARD
}	t_token_type;

typedef struct s_token
{
	token_type	type;
	char		*value;
	int			priority;
}	t_token;
