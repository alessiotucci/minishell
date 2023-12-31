/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:29:34 by atucci            #+#    #+#             */
/*   Updated: 2023/12/31 17:17:51 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"


// pipex(current, current->next);
int	pipex(t_list_of_tok *first, t_list_of_tok *second)
{
	int		pip_fd[2];
	int		first_pid;
	int		second_pid;
	char	**first_command;
	char	**second_command;

	if (ac != 3)
		return (printf("Usage: ./a.out \"command1\"  \"command2\"\n"));
	first_command = ft_split(av[1], ' ');
	second_command = ft_split(av[2], ' ');
	if (pipe(pip_fd) == -1)
	{
		ft_putstr_fd("Failed to create a pipe\n", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	first_pid = fork();
	if (first_pid < 0)
	{
		ft_putstr_fd("Failed to fork for the first time\n", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	if (first_pid == 0)
	{
		dup2(pip_fd[1], STDOUT_FILENO);
		close(pip_fd[0]);
		execvp(first_command[0], first_command);
	}
	second_pid = fork();
	if (second_pid < 0)
	{
		ft_putstr_fd("Failed to fork for the second time\n", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	if (second_pid == 0)
	{
		dup2(pip_fd[0], STDIN_FILENO);
		close(pip_fd[1]);
		execvp(second_command[0], second_command);
	}
	// the end
	close(pip_fd[0]);
	close(pip_fd[1]);
	waitpid(first_pid, NULL, 0);
	waitpid(second_pid, NULL, 0);
	return (0);
}

