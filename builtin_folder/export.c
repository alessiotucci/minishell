/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:42:59 by atucci            #+#    #+#             */
/*   Updated: 2024/01/22 12:38:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define MAX_ENV_VARIABLES 100

/* 8 */
void	print_export_format(char *var, char *value)
{
	printf("declare -x %s=\"%s\"\n", var, value);
}

/* 7 */
int	is_valid_identifier(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* 6 */
void	handle_null_arg(char *env[])
{
	int		i;
	char	*equal_sign;
	char	*value;

	i = 0;
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			value = equal_sign + 1;
			print_export_format(env[i], value);
			*equal_sign = '=';
		}
		i++;
	}
}

/* 5 */
/* Modified to take a pointer to the env array 
void	update_env_var(char ***env, char *key, char *value)
{
	int	j;

	j = 0;
	while ((*env)[j] != NULL)
	{
		if (ft_strncmp((*env)[j], key, ft_strlen(key)) == 0)
		{
			free((*env)[j]);
			(*env)[j] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
			strcpy((*env)[j], key);
			strcat((*env)[j], "=");
			strcat((*env)[j], value);
			print_export_format(key, value);
			break ;
		}
		j++;
	}
}*/
void	update_env_var(char ***env, char *key, char *value)
{
	int	j = 0;
	int	found = 0;

	while ((*env)[j] != NULL)
	{
		if (strncmp((*env)[j], key, strlen(key)) == 0 && (*env)[j][strlen(key)] == '=')
		{
			found = 1;
			break;
		}
		j++;
	}
	*env = my_setenv(*env, key, value, found);
	print_export_format(key, value);
}


/* 4 */
/* Extracted logic for handling case when arg contains a value */
void	handle_value_case(char *arg, char ***env)
{
	char	*equal_sign;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	*equal_sign = '\0';
	value = equal_sign + 1;
	if (!is_valid_identifier(arg))
		printf("export: not an identifier: %s\n", arg);
	else
		update_env_var(env, arg, value);
	*equal_sign = '=';
}

/* 3 */
/* Extracted logic for handling case when arg does not contain a value */
void	handle_empty_value_case(char *arg, char ***env)
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
			while ((*env)[k] != NULL)
				k++;
			(*env)[k] = malloc(strlen(arg) + 1);
			strcpy((*env)[k], arg);
			printf("start ok\n");
			print_export_format(arg, "");
		}
	}
}

/* 2 */
/* Modified to use the new handle_value_case and handle_empty_value_case functions */
void	handle_non_null_arg(char *args[], char ***env)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (strchr(args[i], '=') != NULL)
			handle_value_case(args[i], env);
		else
			handle_empty_value_case(args[i], env);
		i++;
	}
}

/* 1 */
/* Modified to pass a pointer to the env array to handle_non_null_arg */
void	my_export(char *args[], char *env[])
{
	//int	f;

	//f = 0;
	printf("args in position [1]: %s\n", args[1]);
	if (args[1] == NULL)
		handle_null_arg(env);
	else
	{
		handle_non_null_arg(args, &env);
		//f = 1;
	}
	/*printf("***\n");
	if (f == 1)
		print_string_array(env);
	printf("***\n");
	printf("finished execution\n");*/
}

