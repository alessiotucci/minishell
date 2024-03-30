#include "../../minishell.h"
#define MAX_ENV_VARIABLES 100
#include <stdbool.h>

void	my_sprintf(char *buffer, char *key, char *old_value, char *new_value)
{
	int	bufflen;

	bufflen = ft_strlen(buffer);
	ft_strlcpy(buffer, key, ft_strlen(key) + 1);
	ft_strlcat(buffer, "=", bufflen + 2);
	if (old_value != NULL)
		ft_strlcat(buffer, old_value, ft_strlen(old_value) + bufflen + 1);
	ft_strlcat(buffer, new_value, ft_strlen(new_value) + bufflen + 1);
}


char **my_setenv(char **old_env, char *key, char *new_value, int append_flag)
{
	int		i;
	char	*new_entry;
	int		key_len;
	char	*old_value;

	key_len = ft_strlen(key);
	i = 0;
	while (old_env[i] != NULL)
	{
		if (ft_strncmp(old_env[i], key, key_len) == 0
			&& old_env[i][key_len] == '=')
		{
			if (append_flag)
			{
				old_value = old_env[i] + key_len + 1;
				new_entry = malloc(ft_strlen(old_value) + ft_strlen(new_value) + key_len + 3);
				my_sprintf(new_entry, key, old_value, new_value);
			}
			else
			{
				new_entry = malloc(ft_strlen(new_value) + key_len + 2);
				my_sprintf(new_entry, key, NULL, new_value);
			}
			free(old_env[i]);
			old_env[i] = new_entry;
			return (old_env);
		}
		i++;
	}
	old_env = copy_array(old_env, 1);
	new_entry = malloc(ft_strlen(new_value) + key_len + 2);
	my_sprintf(new_entry, key, NULL, new_value);
	old_env[i] = new_entry;
	printf("old_env[i] is '%s', where i is {%d}\n", old_env[i], i);
	//print_string_array(old_env);
	printf("%sold_env address is %p%s\n", YELLOW, old_env, RESET);
	return (old_env);
}
/* 8 */
void	export_format(char *var, char *value)
{
	printf("declare -x %s=\"%s\"\n", var, value);
}

/* 7 */
int	is_valid_identifier(char *str)
{
	int	i;

	printf("WHY NOT VALID: %s\n", str);
	i = 1;
	if (ft_isalpha(str[0]) == false && str[0] != '_')
		return (0);
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == false && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* 6 */
void	without_arguments(char *env[])
{
	int		i;
	char	*equal_sign;
	char	*value;

	i = 0;
	sort_string_array(env);
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			value = equal_sign + 1;
			export_format(env[i], value);
		}
		i++;
	}
}

void	update_env_var(char **env, char *key, char *value)
{
	int	j = 0;
	int	found = 0;

	printf("update_env_var: key %s\n", key);
	while (env[j] != NULL)
	{
		if (strncmp(env[j], key, strlen(key)) == 0 && env[j][strlen(key)] == '=')
		{
			found = 1;
			break;
		}
		j++;
	}
	printf("%snow calling  the  my_setenv function()%s\n", YELLOW, RESET);
	printf("key: [%s], value: [%s], flag[%d]\n", key, value, found);
	env = my_setenv(env, key, value, found);
	//char **slutt = my_setenv(env, key, value, found);
	//env = slutt;
	//export_format(key, value);
}


/* 4 */
/* Extracted logic for handling case when arg contains a value */
void	handle_value_case(char *arg, char **env)
{
	char	*equal_sign;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	value = equal_sign + 1;
	/*if (!is_valid_identifier(arg))
		printf("export: not an identifier: %s\n", arg);
	else*/
		update_env_var(env, arg, value);
	*equal_sign = '=';
}

/* 3 */
/* Extracted logic for handling case when arg does not contain a value */
void	handle_empty_value_case(char *arg, char **env)
{
	char	*existing_value;
	int		k;

	if (!is_valid_identifier(arg))
		printf("export: not an identifier: %s\n", arg);
	else
	{
		existing_value = getenv(arg);
		if (existing_value == NULL)
		{
			k = 0;
			while (env[k] != NULL)
				k++;
			env[k] = malloc(strlen(arg) + 1);
			strcpy(env[k], arg);
		}
	}
	printf("%senv address is %p%s\n", YELLOW, env, RESET);
}

/* 2 HERE WE SHOULD HAVE A SLOT TO INSERT THE STRING
 Modified to use the new handle_value_case
 and handle_empty_value_case functions */
void	handle_non_null_arg(char *args[], char **env)
{
	int	i;
//	int	num_args;

//	num_args = lenght_string_array(args);
//	char	**fake_copy = copy_array(*env, num_args - 1);
//	env = &fake_copy;
	//env = copy_array(*env, num_args -1);
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL)
			handle_value_case(args[i], env); // here it was env
		else
			handle_empty_value_case(args[i], env); // here it was env
		i++;
	}
}

/* 1 */
/* Modified to pass a pointer to the env array to handle_non_null_arg */
void	my_export(char *args[], char *env[])
{
	if (args[1] == NULL)
		without_arguments(env);// arguments are null
	else
		//handle_non_null_arg(args, &env);
		handle_non_null_arg(args, env);
	/*printf("%senv address %p%s\n", RED, env, RESET);
	printf("%s!env address %p%s\n", BG_RED, &env, BG_RESET); */
}
