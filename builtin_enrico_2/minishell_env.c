/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:05:47 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/17 22:06:31 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void minishell_env(char *args[]) {
    // If no arguments provided, print the current environment variables
    if (args[1] == NULL) {
        extern char **environ;
        for (char **env = environ; *env != NULL; env++) {
            printf("%s\n", *env);
        }
    } else {
        fprintf(stderr, "minishell_env: Too many arguments\n");
    }
}

int main(int argc, char *argv[]) {
    minishell_env(argv);

    return 0;
}

