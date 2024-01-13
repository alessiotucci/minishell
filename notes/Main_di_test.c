/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main_di_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:14:41 by atucci            #+#    #+#             */
/*   Updated: 2024/01/13 17:57:32 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <strings.h>
#include "../libft/libft.h"
#include "../minishell.h"
void	*which_built(char *token, char **args, char **env)
{
	(void)env;
	if (token  == NULL)
		return (NULL);
	if (strcmp(token, "echo") == 0)
//		minishell_echo(args);
		printf("%s echo %s\n", GREEN, RESET);
	else if (strcmp(token, "cd") == 0)
//			minishell_cd(args[1]);
		printf("%s cd %s\n", GREEN, RESET);
	else if (strcmp(token, "pwd") == 0)
//		minishell_pwd();
		printf("%s pwd %s\n", GREEN, RESET);
	else if (strcmp(token, "export") == 0)
//		minishell_export(args);
		printf("%s export %s\n", GREEN, RESET);
	else if (strcmp(token, "unset") == 0)
//		minishell_unset(args[1], env);
		printf("%s unset %s\n", GREEN, RESET);
	else if (strcmp(token, "env") == 0)
//		minishell_env(env);
		printf("%s env %s\n", GREEN, RESET);
	else if (strcmp(token, "exit") == 0)
//		minishell_exit(args); // what value give to this? 
		printf("%s exit %s\n", GREEN, RESET);
	return (NULL);
}

//env_copy
// invece che uscire con errore, ritornare null (?)
static char	**copy_array(char **env)
{
	int		env_count;
	char	**env_copy;
	int		i;

	env_count = 0;
	while (env[env_count] != NULL)
		env_count++;
	env_copy = (char **)malloc((env_count + 1) * sizeof(char *));
	if (env_copy == NULL)
		return (perror("Error in memory allocation"), NULL);
	i = 0;
	while (env[i] != NULL)
	{
		env_copy[i] = ft_strdup(env[i]);
		if (env_copy[i] == NULL)
			return (perror("Error in memory allocation"), NULL);
		i++;
	}
	env_copy[env_count] = NULL;
	return (env_copy);
}

// COMPILARE IN QUESTO MODE
//e3r12p3% gcc Main_di_test.c ../libft/libft.a 

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**matrix;
	char	**copy_env = copy_array(env);
	while (1)
	{
		input = readline(BLUE"minishelly>"RESET);
		matrix = ft_split(input, ' ');
		which_built(matrix[0], matrix, copy_env);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
