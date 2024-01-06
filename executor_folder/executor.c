/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/06 14:21:10 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
const char *namey[] =
{
	"Command",
	"Flag",
	"Builtin",
	"Parenthesis",
	"Dollar",
	"Pipes",
	"Redirection in",
	"Redirection out",
	"Redirection appender",
	"Here Documents",
	"Logical Operator",
	"Command Arguments",
	"File Name "
};


/* 5 function in this file 
 * This function goes through the list and look for commands,
 * it return the first it finds !
 * */
t_list_of_tok	*find_command_in_list(t_list_of_tok **head)
{
	t_list_of_tok	*cmd_nod;

	cmd_nod = *head;
	while (cmd_nod != NULL)
	{
		if (cmd_nod->type == T_COMMAND || cmd_nod->type == T_BUILTIN)
			return (cmd_nod);
		cmd_nod = cmd_nod->next;
	}
	return (NULL);
}

/* 4) this functinon needs to be written entirely 
 * it has being copy and paste from bingAi again
 *
 * */
static int	find_redirect(t_list_of_tok *cmd_node)
{
	t_list_of_tok	*iterator;

	iterator = cmd_node;
	while (iterator != NULL)
	{
		if (iterator->type == T_REDIR_OUT || iterator->type == T_REDIR_APP || iterator->type == T_REDIR_IN)
		{
			if (iterator->next == NULL)
			{
				printf("minishesh: parse error near '\\n\'\n");
				return (1);
			}
			if (iterator->next->type == T_FILE_NAME)
			{
				cmd_node->file_name = ft_strdup(iterator->next->token);
				//printf("cmd_node->token:(%s) and cmd_node->filename:(%s)\n", cmd_node->token, cmd_node->file_name);
				return (0);
			}
		}
		iterator = iterator->next;
	}
	return (0);
}

/*3)
 this fuction handle the redirection process
 redirection_process(current, current->next->type);
  !! there is a issue with this functin !! 
  try launch the norminette libft > fiile @
 */
void	redirection_process(t_list_of_tok *cmd_nod, t_type_of_tok type)
{
	printf("FUNCTION-> redirection_process(); [%s] %s {%s}%s\n", cmd_nod->token, BG_RED, namey[cmd_nod->type], BG_RESET);
	if (type == T_FLAG || type == T_COMMAND_ARGS)
		redirection_process(cmd_nod->next, cmd_nod->next->type);
	if (type == T_REDIR_IN)
		redirect_input(cmd_nod->file_name);
	else if (type == T_REDIR_OUT || type == T_REDIR_APP)
	{
		printf("Node of token: [%s] has file_name of [%s]\n", cmd_nod->token, cmd_nod->file_name);
		redirect_output(cmd_nod, type);
	}
	else if (type == T_HERE_DOC)
		here_document(cmd_nod->file_name);
//	else
//		print_node(cmd_nod);
}

static void	piping_process(t_list_of_tok *cmd_nod)
{
	if (cmd_nod->fd_pipe_in != STDIN_FILENO)
		dup2(cmd_nod->fd_pipe_in, STDIN_FILENO);
	if (cmd_nod->fd_pipe_out != STDOUT_FILENO)
		dup2(cmd_nod->fd_pipe_out, STDOUT_FILENO);
}
/*
static void	close_fds(t_list_of_tok *cmd_nod)
{
	if (cmd_nod->fd_pipe_in != STDIN_FILENO)
		close(cmd_nod->fd_pipe_in);
	if (cmd_nod->fd_pipe_out != STDOUT_FILENO)
		close(cmd_nod->fd_pipe_out);
}
*/
/* 2)
 * first handle the redirection
 * then check for builtins, after perform built in, restore fd (?)
 * otherwise fork and go on with execve, after that restore fd (?)
*/
void	*execute_command(char *command, char **args_a, char **envp, t_list_of_tok *cmd_nod)
{
	pid_t	fix_pid;
	int	stdout_copy = dup(STDOUT_FILENO);

	printf("%sFunciton-> Execute_command()%s;\n\tCommand: {%s},\n\targs[1]: {%s}\n",BG_YELLOW, BG_RESET, command, args_a[1]);
	printf("\ncmd_nod->file_name != NULL (%s)\n", cmd_nod->file_name);
	if (cmd_nod->file_name != NULL)
		redirection_process(cmd_nod, cmd_nod->next->type); // here the fd are changed
		piping_process(cmd_nod);
	if (cmd_nod->type == T_BUILTIN)
	{
		fprintf(stdout, "Builtins: %s%s\t(%s)%s\n", BLUE, cmd_nod->token, command, RESET);
		fprintf(stdout, "%s\tFd_in:%s %d %sFd_out:%s %d\n\n", RED, RESET,cmd_nod->fd_pipe_in, YELLOW, RESET, cmd_nod->fd_pipe_out);
		which_built_in(cmd_nod, args_a, envp);
		// Restore the original stdout file descriptor
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
//		return NULL;
	}
	else
	{
		fprintf(stdout, "Command: %s%s\t(%s)%s\n", GREEN, cmd_nod->token, command, RESET);
		fprintf(stdout, "%s\tFd_in:%s %d %sFd_out:%s %d\n\n", RED, RESET,cmd_nod->fd_pipe_in, YELLOW, RESET, cmd_nod->fd_pipe_out);
		fix_pid = fork();
		if (fix_pid == 0)
		{
			//close_fds(cmd_nod);
			execve(command, args_a, envp);
			perror("execve"); // execve returns only on error
			//exit(EXIT_FAILURE);
		}
		else
		{
			//close_fds(cmd_nod);
			wait(NULL);
		}
	}
dup2(stdout_copy, STDOUT_FILENO);
close(stdout_copy);
return (NULL);
}

/* 1) Main function to execute the program
 * I go find the first command in the list
 * Inside the node of the command I update the filename
 * if there is a redirection, the command string take the
 * token of the node 
 * */
int	executor(t_list_of_tok **head, char **envp)
{
	char			*command;
	char			**argoums;
	t_list_of_tok	*cmd_node;

	cmd_node = find_command_in_list(head);
	while (cmd_node != NULL)
	{
		if (find_redirect(cmd_node) == 1)
			break ;
		find_pipes(cmd_node);
		command = cmd_node->token;
		if (cmd_node->type != T_BUILTIN)
			command = find_path_command(cmd_node->token, envp);
		if (command == NULL)
			return (free(command), printf(" Command not found: %s\n", cmd_node->token));
			//command = cmd_node->token;
		argoums = array_from_list(&cmd_node);
		execute_command(command, argoums, envp, cmd_node);
		cmd_node = find_command_in_list(&cmd_node->next);
	}
	return (0);
}
