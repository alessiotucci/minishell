/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:42:59 by atucci            #+#    #+#             */
/*   Updated: 2024/01/20 17:50:45 by atucci           ###   ########.fr       */
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
	// Controlla se la stringa è un identificatore valido
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		return 0;
	}

	int i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			return 0;
		}
		i++;
	}

	return 1;
}

void my_export(char *args[], char *env[])
{
	if (args[1] == NULL)
	{
		// Visualizza l'elenco delle variabili d'ambiente
		int i = 0;
		while (env[i] != NULL)
		{
			char *equal_sign = strchr(env[i], '=');
			if (equal_sign != NULL)
			{
				*equal_sign = '\0';
				char *value = equal_sign + 1;
				print_export_format(env[i], value);
			}
			i++;
		}
	}
	else
	{
		// Analizza e imposta/aggiorna le variabili d'ambiente
		int i = 1;
		while (args[i] != NULL)
		{
			char *equal_sign = strchr(args[i], '=');

			if (equal_sign != NULL)
			{
				// Contiene un valore, effettua controlli sull'identificatore
				*equal_sign = '\0';
				char *value = equal_sign + 1;

				if (!is_valid_identifier(args[i]))
				{
					printf("export: not an identifier: %s\n", args[i]);
				}
				else
				{
					// Controlla e aggiorna manualmente
					int j = 0;
					while (env[j] != NULL)
					{
						if (strncmp(env[j], args[i], strlen(args[i])) == 0)
						{
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
			}
			else
			{
				// Non contiene un valore, gestisci come se avesse un valore vuoto
				if (!is_valid_identifier(args[i]))
				{
					printf("export: not an identifier: %s\n", args[i]);
				}
				else
				{
					char *existing_value = getenv(args[i]);

					int j = 0;
					while (env[j] != NULL)
					{
						if (existing_value == NULL)
						{
							// Variabile non esistente, cerca spazio libero e imposta manualmente
							int k = 0;
							while (env[k] != NULL)
							{
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

