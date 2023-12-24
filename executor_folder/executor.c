/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2023/12/24 16:04:52 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**find_path_env(char **env)
{
	int	i;
	char *nully = NULL;
	(void)env;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			nully = env[i] + 5;
			break ;
		}
		i++;
	}
	printf("path env: |%s%s%s|\n",YELLOW, nully, RESET);
	return (ft_split(nully, ':'));
}

t_list_of_tok	*find_command_in_list(t_list_of_tok **head)
{
	t_list_of_tok	*current;

	current = *head;
	while (current != NULL)
	{
		if (current->type == T_COMMAND || current->type == T_BUILTIN)
			return (current);
		current = current->next;
	}
	return (NULL);
}
void	executor(t_list_of_tok **head, char **envp)
{
	int		i;
	int		y;
	char	**directs;
	char	*command = NULL;
	char	*possible_command;
	t_list_of_tok *current = find_command_in_list(head);
	if (current == NULL)
	{
		printf("there is no command in the string sadly\n");
		return ;
	}
	printf("%s: this  is what\n", current->command_as_string);
	(void)head;
	i = 0;
	directs = find_path_env(envp);
	while (directs[i] != NULL)
	{
		y = ft_strlen(directs[i]) + ft_strlen(current->command_as_string) + 2;
		possible_command = malloc(ft_strlen(directs[i]) + ft_strlen(current->command_as_string) + 2); // +2 for the '/' and '\0'
		printf("y:%d\n", y);
		ft_strlcpy(possible_command, directs[i], y);
		ft_strlcat(possible_command, "/", y);
		ft_strlcat(possible_command, current->command_as_string, y);
		//printf("input_parts[0]: %s\n directs[%d]: %s\n", input_parts[0], i, directs[i]);
		if (access(possible_command, X_OK) == 0)// Check if the command is executable
		{
			command = possible_command;
			break;
		}
		free(possible_command);
		i++;
	}
	printf("commad %s\n", command);
	executor2();
	executor3();
	return ;
}
