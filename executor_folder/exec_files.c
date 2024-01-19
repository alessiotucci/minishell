/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:14:57 by atucci            #+#    #+#             */
/*   Updated: 2024/01/11 19:11:21 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Opening a file for single redirection > */
// int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

/* Opening a file for double redirection >> */
// int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

void	*here_document(char *delimeter)
{
	char	*line;
	int		fd;
	int		fd_in;
	printf("the delimeter is (%s)\n", delimeter);
	fd = open(".txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		line = readline("HEREDOC> ");
		if (my_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd_in = open(".txt", O_RDONLY);
	//if (dup2(fd_in, STDIN_FILENO) == -1)
	//	return(perror("dup2"), NULL);
	//close(fd_in);
	printf("printf fd_in [%d]\n", fd_in);
	return (NULL);
}

/* this function handles the here_doc 
void	*here_document(char *delimiter)
{
	(void)delimiter;
	//char	buffer[1024]; // copy from bing
	char	file_name[] = "heredoc";
	int		temp_fd;
	int		new_fd;
	//size_t	bytes_read;

	temp_fd = open(file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); // Create a temporary file.
	if (temp_fd == -1)
		return (perror("open"), NULL);
	new_fd = open(file_name, O_RDONLY);
	if (new_fd == -1)
		return (perror("open"), NULL);
	if (dup2(new_fd, STDIN_FILENO) == -1)
		return (perror("dup2"), NULL);
	close(temp_fd);
	close(new_fd);
	unlink(file_name);
	return (NULL);
}*/
/*this function check if the type of redirection is either > or >> and behave */
void	redirect_output(char *file_name, t_type_of_tok type)
{
	int	fd;

	if (type == T_REDIR_OUT)
		fd = open(file_name, OVERWRITE_FLAGS, 0666);
	else
		fd = open(file_name, APPEND_FLAGS, 0666);
	//printf("Redirect OUTPUT:%s FD %d%s\n", RED, fd, RESET);
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
		return(perror("dup2"), 1);
	close(new_fd);
	return (0);
}
