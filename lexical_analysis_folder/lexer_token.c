/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:50:51 by atucci            #+#    #+#             */
/*   Updated: 2023/12/08 21:05:55 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_type_of_tok	type_of_token(char *spitted)
{
//	printf("this %s\n", spitted);
	if (is_pipe(spitted))
		return (T_PIPES);
	else if (is_file_reader(spitted))
		return (T_REDIR_IN);
	else if (is_file_writer(spitted))
		return (T_REDIR_OUT);
	else if (is_delimiter(spitted))
		return (T_REDIR_DELIMER);
	else if (is_file_appender(spitted))
		return (T_REDIR_APP);
	else
		return (T_COMMAND);
}
