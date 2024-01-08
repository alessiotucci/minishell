#include "../../minishell.h"
#include "../../libft/libft.h"
#include <errno.h>
#include <string.h>

int	main(int ac, char **av)
{
	int		pip_fd[2];
	int		pid;
	char	**command;
	char	***commands;
	int		i;

	if (ac < 3)
		return (printf("Usage: ./a.out \"command1\"  \"command2\" ...\n"));
	commands = malloc(sizeof(char **) * ac);
	i = 1;
	while ( i < ac)
	{
		commands[i - 1] = ft_split(av[i], ' ');
		i++;
	}
	commands[i - 1] = NULL;
	i = 0;
	while (i < ac - 2)
	{
		if (pipe(pip_fd) == -1)
			return (1);
		pid = fork();
		if (pid == 0)
		{
			dup2(pip_fd[1], STDOUT_FILENO);
			close(pip_fd[0]);
			execvp(commands[i][0], commands[i]);
		}
		else
		{
			waitpid(pid, NULL, 0);
			dup2(pip_fd[0], STDIN_FILENO);
			close(pip_fd[1]);
		}
	i++;
	}
	command = commands[ac - 2];
	execvp(command[0], command);
	return (0);
}

