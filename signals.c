/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:02:56 by atucci            #+#    #+#             */
/*   Updated: 2023/12/11 13:27:13 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function is the signal handler for the SIGINT signal,
 which is sent when the user presses Ctrl+C.
 It clears the current line in the readline buffer,
 moves the cursor to a new line, and redraws the prompt.
 This gives you a new prompt on a new line when you press Ctrl+C
 
void	handle_ctrl_c(int sig)
{
	(void)sig;
		printf("handling signales with ctrl-c\n");
	printf("\n");
	exit(0);
}
here it goes into segfault
void	handle_ctrl_d(int sig)
{
	(void)sig;
	printf("handling an other signals\n");
	exit(0);
}

void	handle_ctrl_backlash(int sig)
{
	(void)sig;
		printf("handling signal with ctrl-boh \n");
		exit(0);
}
*/
void handle_ctrl_c(int sig) 
{
	(void)sig;
	rl_replace_line("", 0);  // Clear the current line
	rl_on_new_line();		// Move the cursor to a new line
	rl_redisplay();		  // Redisplay the prompt
}

// Signal handler for SIGQUIT (Ctrl+\)
void handle_ctrl_backlash(int sig) 
{
	(void)sig;
	printf("\nHandling signal with Ctrl+\\ \n");
	exit(0);  // Adjust 0 as needed
}

// Signal handler for SIGTERM (default termination signal)
void handle_termination(int sig) 
{
	(void)sig;
	printf("\nHandling termination signal \n");
	exit(0);  // Adjust exit_code as needed
}
/*
		TO DO 
		* include the global variable for exit code
		* use the rl_replace_line, and rl_on_new_line
		* use the rl_redisplay function.
*/
