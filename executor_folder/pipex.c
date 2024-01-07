/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:29:34 by atucci            #+#    #+#             */
/*   Updated: 2024/01/06 18:27:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

/**
 * This function sets up a pipe between two commands.
 *
 * @param first_cmd Pointer to the first command node.
 * @param secnd_cmd Pointer to the second command node.
 */
void	set_pipes(t_list_of_tok *first_cmd, t_list_of_tok *secnd_cmd)
{
	int	fd[2];  /* File descriptors for the pipe */

	printf("*** Piping [%s] with [%s] ***\n", first_cmd->token, secnd_cmd->token);
	if (pipe(fd) == -1)
		return (perror("pipe"));
	/* If pipe creation fails, print an error message and return */
	first_cmd->fd_pipe_out = fd[1];
	secnd_cmd->fd_pipe_in = fd[0];
	/* Set the write end of the pipe (fd[1]) as the output for the first command */
	/* Set the read end of the pipe (fd[0]) as the input for the second command */
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

