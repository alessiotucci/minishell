/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:55:47 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/06 17:56:46 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int minishell_pwd(void) {
    char cwd[1024]; // Assumiamo che il percorso non superi i 1024 caratteri

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("minishell");
        return 1; // Ritorna un codice di errore in caso di fallimento
    }

    return 0; // Ritorna il codice di uscita appropriato
}
