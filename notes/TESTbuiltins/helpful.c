#include "../../minishell.h"

// Function to implement the 'unset' built-in
void minishell_unset(char *var_name, char *envp[]) 
{
	char	**env;
	int		found;
	char	**p;

	found = 0;
	env = envp;
	if (var_name == NULL || envp[1] == NULL)
		return ;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, var_name, ft_strlen(var_name)) == 0 &&
			(*env)[ft_strlen(var_name)] == '=')
		{
			found = 1;
			break;
		}
		env++;
	}
	if (found)
	{
		p = env;
		while (*p != NULL)
		{
			*p = *(p + 1);
			p++;
		}
		//printf("Unset variable: %s\n", var_name);
	}
	//else
		//printf("Variable not found: %s\n", var_name);
	//printf("%senvP address is %p%s\n", YELLOW, envp, RESET);
}

/* If no arguments provided, print the current environment variables
 * we need to double check this case
 */
void	minishell_env(char **env)
{
	// you can simply this and delete
	int	i;

	i = 0;
	int l = lenght_string_array(env);
	printf("the lenght  of env is %d\n", l);
	while (i <= l - 1)
	{
		printf("%s \n", env[i]);
		//printf("%d \n", i);
		i++;
	}
	printf("%senv address is %p%s\n", YELLOW, env, RESET);
}

void	handle_signal(int signal)
{
	printf("signal receive%d\n", signal);
	exit(1);
}
