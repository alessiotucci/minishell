/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 09:14:57 by atucci            #+#    #+#             */
/*   Updated: 2023/12/27 08:56:16 by atucci           ###   ########.fr       */
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
	printf("redirect_input function, fd: [%d]\n", fd);
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

/*this function has just being copy and pasted form bing so I need to recheck */
void	redirect_output(t_list_of_tok *current, t_type_of_tok type)
{
	int	fd;
	printf("%sFANCULO FANCULTO%s",BG_GREEN, BG_RESET);
	//fd = 1; // to silence the warning 
	if (type == T_REDIR_OUT)
	{
		fd = open(current->file_name, OVERWRITE_FLAGS, 0666);
		printf("%susing overwrite flags: %s",BG_GREEN, BG_RESET);
	}
	else// if (type == T_REDIR_APP)
	{
		fd = open(current->file_name, APPEND_FLAGS, 0666);
		printf("%susing append flags: %s",BG_CYAN, BG_RESET);
	}
	//else if (type == T_REDIR_IN)
	//	redirect_input(current->file_name);
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
