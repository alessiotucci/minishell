/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:18:49 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/11 17:15:20 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_list	*start_back(t_list *here_doc_lst)
// {
// 	while (here_doc_lst && here_doc_lst->prev)
// 		here_doc_lst = here_doc_lst->prev;
// 	return (here_doc_lst);
// }

// struct s_list	*get_here_doc(struct s_list **here_doc_lst)
// {
// 	t_list	*res;

// 	res = *here_doc_lst;
// 	if ((*here_doc_lst)->next)
// 		*here_doc_lst = (*here_doc_lst)->next;
// 	return (res->content);
// }

// void	*handle_list_heredocs(int op)
// {
// 	static t_list	*here_doc_lst;
// 	char			*here_doc;

// 	if (op == START)
// 	{
// 		here_doc_lst = start_back(here_doc_lst);
// 		ft_lstclear(&here_doc_lst, &del);
// 		here_doc_lst = NULL;
// 	}
// 	else if (op == ADD)
// 	{
// 		here_doc = here_doc_name();
// 		ft_lstadd_back(&here_doc_lst, ft_lstnew(here_doc));
// 		return (here_doc);
// 	}
// 	else if (op == LIST)
// 		return (start_back(here_doc_lst));
// 	else if (op == GET)
// 		return (get_here_doc(&here_doc_lst));
// 	return (NULL);
// }

// int	reading(int fd, char *del, t_mini *mini)
// {
// 	char	*str;

// 	signal(SIGINT, handle_here_doc_sig);
// 	while (1)
// 	{
// 		str = readline("heredoc> ");
// 		if (str == NULL)
// 		{
// 			printf("\n");
// 			free(str);
// 			free(del);
// 			exit(0);
// 		}
// 		if (ft_strcmp(str, del) == 0)
// 			break ;
// 		str = expander(mini, str);
// 		write(fd, str, ft_strlen(str));
// 		write(fd, &"\n", 1);
// 		free(str);
// 	}
// 	free(str);
// 	free(del);
// 	exit(0);
// }

// void	handle_here_doc(char *del, t_mini *mini)
// {
// 	char	*here_doc;
// 	int		fd;
// 	int		pid;
// 	int		exit_status;

// 	here_doc = handle_list_heredocs(ADD);
// 	fd = open(here_doc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	signal(SIGINT, SIG_IGN);
// 	pid = fork();
// 	if (!pid)
// 		reading(fd, del, mini);
// 	waitpid(pid, &exit_status, 0);
// 	free(del);
// 	g_last_exit_status_cmd = WEXITSTATUS(exit_status);
// 	close(fd);
// }
