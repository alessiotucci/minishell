/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:14:57 by atucci            #+#    #+#             */
/*   Updated: 2024/01/20 16:10:51 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* this function handles the here_doc  */
void	*here_document(char *delimiter)
{
	char	*line;
	int		temp_fd;
	(void)delimiter;

	temp_fd = open(".txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (temp_fd == -1)
		return (perror("open"), NULL);
	while (1)
	{
		line = readline(YELLOW"HEREDOC "RESET);
		if (my_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	close(temp_fd);
	temp_fd  = open(".txt", O_RDONLY);
	if (temp_fd == -1)
		return (perror("open"), NULL);
	if (dup2(temp_fd, STDIN_FILENO) == -1) // this need to be changed
		return (perror("dup2"), NULL);
	close(temp_fd);
	unlink(".txt");
	return (NULL);
}

/*this function check if the type of redirection is either > or >> and behave */
void	redirect_output(char *file_name, t_type_of_tok type)
{
	int	fd;

	if (type == T_REDIR_OUT)
		fd = open(file_name, OVERWRITE_FLAGS, 0666);
	else
		fd = open(file_name, APPEND_FLAGS, 0666);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

/*this function will handle the case
 * where the input is redirect instead of the output*/
int	redirect_input(char *file_name)
{
	int	new_fd;

	new_fd = open(file_name, O_RDONLY);
	if (new_fd == -1)
	{
		close(new_fd);
		return (perror("open"), 1);
	}
	if (dup2(new_fd, STDIN_FILENO) == -1)
		return (perror("dup2"), 1);
	close(new_fd);
	return (0);
}
