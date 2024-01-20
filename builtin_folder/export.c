/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:42:59 by atucci            #+#    #+#             */
/*   Updated: 2024/01/20 18:47:12 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


#define MAX_ENV_VARIABLES 100

void print_export_format(char *var, char *value)
{
	printf("declare -x %s=\"%s\"\n", var, value);
}

int is_valid_identifier(char *str)
{
	int	i;

	i = 1;
	// Check if the string is a valid identifier
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
		i++;
	}
	return 1;
}

void my_export(char *args[], char *env[])
{
	if (args[1] == NULL)
	{
		// Display the list of environment variables
		int i = 0;
		while (env[i] != NULL)
		{
			char *equal_sign = strchr(env[i], '=');
			if (equal_sign != NULL)
			{
				*equal_sign = '\0';
				char *value = equal_sign + 1;
				print_export_format(env[i], value);
				*equal_sign = '=';  // Restore the original content
			}
			i++;
		}
	}
	else
	{
		// Parse and set/update environment variables
		int i = 1;
		while (args[i] != NULL) {
			char *equal_sign = strchr(args[i], '=');

			if (equal_sign != NULL) {
				// Contains a value, perform checks on the identifier
				*equal_sign = '\0';
				char *value = equal_sign + 1;

				if (!is_valid_identifier(args[i])) {
					printf("export: not an identifier: %s\n", args[i]);
				} else {
					// Check and update manually
					int j = 0;
					while (env[j] != NULL) {
						if (strncmp(env[j], args[i], strlen(args[i])) == 0) {
							free(env[j]);
							env[j] = malloc(strlen(args[i]) + strlen(value) + 2);
							strcpy(env[j], args[i]);
							strcat(env[j], "=");
							strcat(env[j], value);
							print_export_format(args[i], value);
							break;
						}
						j++;
					}
				}
				*equal_sign = '=';  // Restore the original content
			} else {
				// Does not contain a value, handle as if it has an empty value
				if (!is_valid_identifier(args[i])) {
					printf("export: not an identifier: %s\n", args[i]);
				} else {
					char *existing_value = getenv(args[i]);

					int j = 0;
					while (env[j] != NULL) {
						if (existing_value == NULL) {
							// Variable does not exist, find free space and set manually
							int k = 0;
							while (env[k] != NULL) {
								k++;
							}
							env[k] = malloc(strlen(args[i]) + 1);
							strcpy(env[k], args[i]);
							print_export_format(args[i], "");
							break;
						}
						j++;
					}
				}
			}
			i++;
		}
	}
}
