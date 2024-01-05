/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:29:34 by atucci            #+#    #+#             */
/*   Updated: 2024/01/05 11:51:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	set_pipes(t_list_of_tok *first_cmd, t_list_of_tok *secnd_cmd)
{
	int	fd[2];

	printf("*** Piping [%s] with [%s] ***\n", first_cmd->token, secnd_cmd->token);
	if (pipe(fd) == -1)
		return (perror("pipe"));
	first_cmd->fd_pipe = fd[1];
	secnd_cmd->fd_pipe = fd[0];
	printf("[%s] fd is %d\n[%s] fd is %d\n", first_cmd->token, first_cmd->fd_pipe, secnd_cmd->token, secnd_cmd->fd_pipe);
}

void	find_pipes(t_list_of_tok *head)
{
	t_list_of_tok	*current;
	t_list_of_tok	*first_cmd;
	t_list_of_tok	*second_cmd;

	first_cmd = find_command_in_list(&head);
	current = head;
	while (current != NULL)
	{
		if (current->type == T_PIPES)
		{
			second_cmd = find_command_in_list(&head);
			set_pipes(first_cmd, second_cmd);
			break ;
		}
		current = current->next;
	}
}
/* pipex(current, current->next);
int	pipex(t_list_of_tok *first, t_list_of_tok *second)
{

}
*/
