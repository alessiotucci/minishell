/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:29:34 by atucci            #+#    #+#             */
/*   Updated: 2024/01/12 17:39:17 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

/**
 * This function sets up a pipe between two commands.
 * @param first_cmd Pointer to the first command node.
 * @param secnd_cmd Pointer to the second command node.
 */
void	set_pipes(t_list_of_tok *first_cmd, t_list_of_tok *secnd_cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror("pipe"));
	first_cmd->out_file = fd[1];
	secnd_cmd->in_file = fd[0];
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
			second_cmd = find_command_in_list(&(current->next));
			set_pipes(first_cmd, second_cmd);
			break ;
		}
		current = current->next;
	}
}

