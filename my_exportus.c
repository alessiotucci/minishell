/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exportus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:23:09 by atucci            #+#    #+#             */
/*   Updated: 2024/04/01 16:12:08 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	//printf("check this:  ");
	//printf("key:[%s]\tnew_value:[%s]\n\n", key, new_value);
	key_len = ft_strlen(key);
	i = 0;
	while (old_env[i] != NULL)
	{
		if (new_value == NULL) //TODO: fix the segfault
			break ;
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
	old_env = copy_array(old_env, 1); //TODO; this is the DEAL!!
	if (new_value != NULL)
		new_entry = malloc(ft_strlen(new_value) + key_len + 2);
	else
	{
		new_entry = malloc(key_len);
		//printf("new_value is null, ELSE\n");
		new_value = "";
	}
	//printf("new_entry: [%s] key:[%s] new_value:[%s]\n", new_entry, key, new_value);
	my_sprintf(new_entry, key, NULL, new_value);
	old_env[i] = new_entry;
	//printf("'%s', old_env[%d]\n", old_env[i], i);
	//print_string_array(sort_string_array(old_env));
	//printf("the lenght: [%s%d%s]\n", RED, lenght_string_array(old_env), RESET);
	//printf("%sold_env  is\n%p%s\n", RED, old_env, RESET);
	return (old_env);
}
/* 8 */
void	export_format(char *var, char *value)
{
	printf("declare -x %s=\"%s\"\n", var, value);
}

/* 7 I need to double check if the var is valid for exporting */
int	is_valid_identifier(char *str)
{
	int	i;

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
/* here I call set env that is working with OLDPWD PWD in the cd builtins */
//void update_env_var(char ***env, char *key, char *value)
char **update_env_var(char **env, char *key, char *value)
{
	int	j = 0;
	int	found = 0;

	//printf("update_env_var: key %s\n", key);
	while (env[j] != NULL)
	{
		if (strncmp(env[j], key, strlen(key)) == 0 && env[j][strlen(key)] == '=')
		{
			found = 1;
			break;
		}
		j++;
	}
	//printf("%snow calling  the  my_setenv function()%s\n", YELLOW, RESET);
	//printf("key: [%s], value: [%s], flag[%d]\n", key, value, found);
	//printf("prima: %p\n", env);
	env = my_setenv(env, key, value, found);
	return (env);
	//printf("dopo: %p\n***\n", env);
	//export_format(key, value);
}


/* 4 */
/* Extracted logic for case when VAR=123 for example */
char **handle_equals(char *arg, char **env)
{
	char	*equal_sign;
	char	*value;

	printf("%sHANDLE EQUALS%s\n", YELLOW,    RESET);
	equal_sign = ft_strchr(arg, '=');
	value = equal_sign + 1;
	/*if (!is_valid_identifier(arg))
		printf("export: not an identifier: '%s'\n", arg);
	else*/
	env = update_env_var(env, arg, value);
	*equal_sign = '=';
	return (env);
}

/* 3 */
/* Extracted logic for handling case when var does not contain a value */
char	**empty_var(char *arg, char **env)
{
	char	*existing_value;

	if (!is_valid_identifier(arg))
		printf("export: not an identifier: '%s'\n", arg);
	else
	{
		existing_value = getenv(arg);
		if (existing_value == NULL)
			env = my_setenv(env, arg, NULL, 0);
	}
	return (env);
}

/* 2 HERE WE SHOULD HAVE A SLOT TO INSERT THE STRING
 Modified to use the new handle_value_case
 and handle_empty_value_case functions */
char	**export_variable(char *args[], char **env)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL)
			env = handle_equals(args[i], env);
		else
			env = empty_var(args[i], env); // here it was env
		i++;
	}
	return env;
}
/* 2: export is being called without arguments */
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

/* 1 */
/* Modified to pass a pointer to the env array to handle_non_null_arg */
char	**my_exportus(char *args[], char *env[])
{
	if (args[1] == NULL)
		without_arguments(env);// arguments are null
	else
		env = export_variable(args, env);
	return (env);
}


