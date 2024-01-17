/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:49:23 by enricogiral       #+#    #+#             */
/*   Updated: 2024/01/17 11:38:21 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ENV_VARIABLES 100

void print_export_format(char *var, char *value) {
    printf("declare -x %s=\"%s\"\n", var, value);
}

void my_export(char *args[], char *env[]) 
{
    if (args[1] == NULL) {
        // Visualizza l'elenco delle variabili d'ambiente
        int i = 0;
        while (env[i] != NULL) 
        {
            char *equal_sign = strchr(env[i], '=');
            if (equal_sign != NULL) 
            {
                // Contiene un valore, visualizza nel formato richiesto
                *equal_sign = '\0';  // Termina la stringa prima dell'uguale
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
                // Contiene un valore, imposta/aggiorna manualmente
                *equal_sign = '\0';  // Termina la stringa prima dell'uguale
                char *value = equal_sign + 1;
                char *existing_value = getenv(args[i]);

                if (existing_value != NULL) 
                {
                    // Variabile già esistente, cerca e aggiorna manualmente
                    int j = 0;
                    while (env[j] != NULL) 
                    {
                        if (strncmp(env[j], args[i], strlen(args[i])) == 0) 
                        {
                            free(env[j]);  // Libera la memoria precedente
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
                else 
                {
                    // Variabile non esistente, cerca spazio libero e imposta manualmente
                    int j = 0;
                    while (env[j] != NULL) 
                    {
                        j++;
                    }
                    env[j] = malloc(strlen(args[i]) + strlen(value) + 2);
                    strcpy(env[j], args[i]);
                    strcat(env[j], "=");
                    strcat(env[j], value);
                    print_export_format(args[i], value);
                }
            } 
            else 
            {
                // Non contiene un valore, gestisci come se avesse un valore vuoto
                char *existing_value = getenv(args[i]);

                int j = 0;
                while (env[j] != NULL) {
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
            i++;
        }
    }
}


int main(int argc, char *argv[], char *env[]) {
    my_export(argv, env);
    return 0;
}
