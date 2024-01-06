/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:49:23 by enricogiral       #+#    #+#             */
/*   Updated: 2024/01/06 18:51:50 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("Usage: %s VARIABLE VALUE\n", argv[0]);
        return 1;
    }

    char *variable = argv[1];
    char *value = argv[2];

    // Set the environment variable
    if (setenv(variable, value, 1) != 0) 
    {
        printf("Error setting environment variable\n");
        perror(NULL); // This will print the error message to stderr
        return 1;
    }

    // Print the exported variable and its value
    printf("export %s=\"%s\"\n", variable, value);

    // Example of using getenv to retrieve the value
    char *retrievedValue = getenv(variable);
    if (retrievedValue != NULL) 
    {
        printf("Retrieved value using getenv: %s\n", retrievedValue);
    } 
    else 
    {
        printf("Environment variable not found\n");
    }

    return 0;
}
