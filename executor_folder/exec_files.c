/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:14:57 by atucci            #+#    #+#             */
/*   Updated: 2024/01/01 16:26:47 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Opening a file for single redirection > */
// int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

/* Opening a file for double redirection >> */
// int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

/*this function will handle the case where the input is redirect instead of the output*/
void	redirect_input(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
//	printf("redirect_input function, fd: [%d]\n", fd);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
	close(fd);
	return ;
}
/* this function handles the here_doc */
void	here_document(char *delimiter)
{
	char	buffer[1024]; // copy from bing
	char	file_name[] = "heredoc";
	int		temp_fd;
	int		new_fd;
	size_t	bytes_read;

	temp_fd = open(file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); // Create a temporary file.
	if (temp_fd == -1)
	{
		perror("open");
		return ;
	}
	while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) -1)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (my_strcmp(buffer, delimiter) == 0)
			break ;
		write(temp_fd, buffer, bytes_read);
	}
	new_fd = open(file_name, O_RDONLY);
	if (new_fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(new_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
	close(temp_fd);
	close(new_fd);
	unlink(file_name);
}
/*this function check if the type of redirection is either > or >> and behave */
void	redirect_output(t_list_of_tok *current, t_type_of_tok type)
{
	int	fd;

	if (type == T_REDIR_OUT)
		fd = open(current->file_name, OVERWRITE_FLAGS, 0666);
	else
		fd = open(current->file_name, APPEND_FLAGS, 0666);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
