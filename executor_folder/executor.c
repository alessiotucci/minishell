/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/10 12:46:40 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
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
				cmd_node->redirect_type = iterator->type; // latest update we need more variables
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
 */
void	redirection_process(char *file_name, t_type_of_tok type)
{
	//printf("%sFUNCTION-> redirection_process()%s;\n\tfile_name: [%s] type_parameter {%s}\n", BG_RED, BG_RESET, file_name, namey[type]);
	if (type == T_REDIR_IN)
		redirect_input(file_name);
	else if (type == T_REDIR_OUT || type == T_REDIR_APP)
		redirect_output(file_name, type);
	else if (type == T_HERE_DOC)
		here_document(file_name);
}

/* this function is suppose to handle the piping if
 * the fd are differente than the standards
*/
void	piping_process(t_list_of_tok *cmd_nod)
{
	if (cmd_nod->in_file != 0)
	{
		dup2(cmd_nod->in_file, STDIN_FILENO);
		//close(cmd_nod->in_file);
		printf("%sCMD NODE->IN_FILE != STDIN!%s\n", RED, RESET); // if this print happens before
	}
	if (cmd_nod->out_file!= 1)
	{
		dup2(cmd_nod->out_file, STDOUT_FILENO);
		//close(cmd_nod->out_file);
		printf("%sCMD NODE->OUT_FILE != STDOUT!%s\n", RED, RESET); // if this print happens before
	}
}

/* last change */
void	restore_original_stdout(int copy)
{
		dup2(copy, STDOUT_FILENO);
		close(copy);
}
/* 2)
 * first handle the redirection
 * then check for builtins, after perform built in, restore fd (?)
 * otherwise fork and go on with execve, after that restore fd (?)
*/
void	*execute_command(char *command, char **args_a, char **envp, t_list_of_tok *cmd_nod)
{
	pid_t	fix_pid;
	int	stdout_copy; // those copy stay STANDARD

	stdout_copy = dup(STDOUT_FILENO);
	printf("%sFunciton-> Execute_command()%s;\n\tCommand: {%s},\n\targs[1]: {%s}\n",BG_YELLOW, BG_RESET, command, args_a[1]);
	printf("\ncmd_nod->file_name != NULL\n\t(%s)\n", cmd_nod->file_name);
	if (cmd_nod->file_name != NULL)
		redirection_process(cmd_nod->file_name, cmd_nod->redirect_type); // why the fd doesnt change here?
	printf("PIPING PROCESS!\n"); // this printf should not be there
	piping_process(cmd_nod); // here the fd are changed too 
	if (cmd_nod->type == T_BUILTIN)
	{
		//////////////////////////////////////////////
		ft_putstr_fd("\nBuiltins\n", stdout_copy);
		ft_putstr_fd("fd_in : ", stdout_copy);
		ft_putnbr_fd(cmd_nod->in_file, stdout_copy);
		ft_putstr_fd("\tfd_out :", stdout_copy);
		ft_putnbr_fd(cmd_nod->out_file, stdout_copy);
		ft_putstr_fd("\n", stdout_copy);
		/////////////////////////////////////////////////
		printf("Builtins: %s%s\t(%s)%s\n", BLUE, cmd_nod->token, command, RESET);
		printf("%s\tFd_in:%s %d %sFd_out:%s %d\n\n", RED, RESET,cmd_nod->in_file, YELLOW, RESET, cmd_nod->out_file);

		which_built_in(cmd_nod, args_a, envp);
		// Restore the original stdout file descriptor
		//restore_original_stdout(stdout_copy);
	}
	else
	{
		/////////////////////////////////////////////
		ft_putstr_fd("\nCommanD:\n", stdout_copy);
		ft_putstr_fd("\tFd_in: ", stdout_copy);
		ft_putnbr_fd(cmd_nod->in_file, stdout_copy);
		ft_putstr_fd(" Fd_out: ", stdout_copy);
		ft_putnbr_fd(cmd_nod->out_file, stdout_copy);
		ft_putstr_fd("\n", stdout_copy);
		//////////////////////////////////////////////
		printf("Command: %s%s\t(%s)%s\n", GREEN, cmd_nod->token, command, RESET);
		printf("%s\tFd_in:%s %d %sFd_out:%s %d\n\n", RED, RESET,cmd_nod->in_file, YELLOW, RESET, cmd_nod->out_file);
		
		fix_pid = fork();
		// TO DO BY ROGER
		// check child process for closingg
		if (fix_pid == 0)
		{
			ft_putstr_fd("\n Processo Figlio", stdout_copy);
			write(stdout_copy, "\n", 1);
			//close(cmd_nod->fd_pipe_in);

			execve(command, args_a, envp);
			perror("execve"); // execve returns only on error
		}
		else
		{
			ft_putstr_fd("\nFather_ProCesS", stdout_copy);
			write(1, "\n", 1);
//			waitpid(fix_pid, &status, 0);
//			close(cmd_nod->fd_pipe_out);
			wait(NULL);
		}
	}
restore_original_stdout(stdout_copy);
return (NULL);
}

/*
 * 1) Main function to execute the program
 * I go find the first command in the list
 * Inside the node of the command I update the filename
 * if there is a redirection, the command string take the
 * token of the node 
 * 
 */
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
		{
			command = find_path_command(cmd_node->token, envp);
			if (command == NULL)
		//		return (free(command), printf(" Command not found: %s\n", cmd_node->token));
				command = cmd_node->token;
		}
		argoums = array_from_list(&cmd_node);
		execute_command(command, argoums, envp, cmd_node);
		cmd_node = find_command_in_list(&cmd_node->next);
	}
	return (0);
}
