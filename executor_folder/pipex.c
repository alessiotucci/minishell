/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:29:34 by atucci            #+#    #+#             */
/*   Updated: 2024/01/21 13:43:35 by atucci           ###   ########.fr       */
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
	printf("We are piping [%s] with [%s]\n", first_cmd->token, secnd_cmd->token);
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror("pipe"));
	first_cmd->out_file = fd[1];
	secnd_cmd->in_file = fd[0];
}

int	find_pipes(t_list_of_tok *head)
{
	t_list_of_tok	*current;
	t_list_of_tok	*first_cmd;
	t_list_of_tok	*second_cmd;

	first_cmd = find_command_in_list(&head);
	current = head;
//	printf("first command token: [%s]\n", first_cmd->token);
//	printf("find-pipe, now exiting\n");
//	exit(0);
	while (current != NULL)
	{
		if (current->type == T_PIPES)
		{
			//if (current->next == NULL)
			//	return (print_and_update("1minishesh: parse error near '\\n\'\n", GENERAL_ERROR), 1);
			printf("Pipex: current->token (%s)\n", current->token);
			second_cmd = find_command_in_list(&(current->next));
			//printf("second_command->token [%s]\n", second_cmd->token);
			if (second_cmd == NULL)
			{
				printf("second command is null\n");
				break ;
			}
			//	return (printf("no node after pipe\n"), 1);
				//return (printf("no command after pipes\n"), 1);
			//printf("second command token: [%s]\n", second_cmd->token);
			set_pipes(first_cmd, second_cmd);
			break ;
		}
		current = current->next;
	}
	return (0);
}
