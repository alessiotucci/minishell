/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/18 11:58:54 by atucci           ###   ########.fr       */
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
 * This function goes throught he list and look for commands,
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
int	redirection_process(char *file_name, t_type_of_tok type)
{
	//printf("%sFUNCTION-> redirection_process()%s;\n\tfile_name: [%s] type_parameter {%s}\n", BG_RED, BG_RESET, file_name, namey[type]);
	if (type == T_REDIR_IN)
		if (redirect_input(file_name))
			return (1);
	if (type == T_REDIR_OUT || type == T_REDIR_APP)
		redirect_output(file_name, type);
	if (type == T_HERE_DOC)
		here_document(file_name);
	return (0);
}

/* this function is suppose to handle the piping if
 * the fd are differente than the standards
*/
void	piping_process(t_list_of_tok *cmd_nod)
{

	if (cmd_nod->in_file != 0)
	{
		dup2(cmd_nod->in_file, STDIN_FILENO);
		close(cmd_nod->in_file);
	}
	if (cmd_nod->out_file!= 1)
	{
		dup2(cmd_nod->out_file, STDOUT_FILENO);
		close(cmd_nod->out_file);
	}
}

/* last change */
void	restore_original_stdout(int copy, t_list_of_tok *cmd_nod)
{
		(void)cmd_nod;
		dup2(copy, STDOUT_FILENO);
		close(copy);
}

void	restore_original_stdin(int copy, t_list_of_tok *cmd_nod)
{
		(void)cmd_nod;
		dup2(copy, STDIN_FILENO);
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
	int	stdout_copy;
	int	stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (cmd_nod->file_name != NULL)
		if (redirection_process(cmd_nod->file_name, cmd_nod->redirect_type))
			return (NULL);
	piping_process(cmd_nod);
	if (cmd_nod->type == T_BUILTIN)
			which_built_in(cmd_nod, args_a, envp);
	else
	{
			fix_pid = fork();
		if (fix_pid == 0)
		{
			execve(command, args_a, envp);
			printf("command not found: %s\n", command);
		}
		else
				wait(NULL);
	}
restore_original_stdout(stdout_copy, cmd_nod);
restore_original_stdin(stdin_copy, cmd_nod);
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
				command = cmd_node->token;
		}
		argoums = array_from_list(&cmd_node);
		execute_command(command, argoums, envp, cmd_node);
		cmd_node = find_command_in_list(&cmd_node->next);
	}
	return (0);
}
