/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:14:57 by atucci            #+#    #+#             */
/*   Updated: 2024/01/10 13:18:32 by atucci           ###   ########.fr       */
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
	int	new_fd;

	new_fd = open(file_name, O_RDONLY);
//	printf("redirect_input function, fd: [%d]\n", fd);
	if (new_fd == -1)
		return (perror("open"));
	if (dup2(new_fd, STDIN_FILENO) == -1)
		return(perror("dup2"));
	close(new_fd);
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
void	redirect_output(char *file_name, t_type_of_tok type)
{
	int	fd;

	if (type == T_REDIR_OUT)
		fd = open(file_name, OVERWRITE_FLAGS, 0666);
	else
		fd = open(file_name, APPEND_FLAGS, 0666);
	printf("Redirect OUTPUT:%s FD %d%s\n", RED, fd, RESET);
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
