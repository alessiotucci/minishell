/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:19:57 by enricogiral       #+#    #+#             */
/*   Updated: 2024/01/17 12:49:24 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

char old_directory[MAX_PATH_LENGTH];

void my_cd(char *directory) 
{
    if (directory == NULL) 
    {
        printf("Usage: cd <directory>\n");
        return;
    }

    // Salva la directory corrente
    char current_directory[MAX_PATH_LENGTH];
    if (getcwd(current_directory, sizeof(current_directory)) == NULL) 
    {
        perror("getcwd");
        return;
    }

    // Salva la vecchia directory
    strcpy(old_directory, current_directory);

    // Cambia la directory
    if (chdir(directory) != 0) 
    {
        perror("cd");
        // Se il cambio di directory fallisce, ripristina la vecchia directory
        chdir(old_directory);
    } 
    else 
    {
        // Stampa il nuovo percorso dopo il cambio di directory
        if (getcwd(current_directory, sizeof(current_directory)) != NULL) 
        {
            printf("%s\n", current_directory);
        } else {
            perror("getcwd");
        }
    }
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    my_cd(argv[1]);

    return 0;
}
