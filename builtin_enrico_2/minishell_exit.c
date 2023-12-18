/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:22:33 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/17 22:19:10 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long g_exit_status;

static void exit_non_numeric_arg(void)
{
    g_exit_status = 2;
    write(STDERR_FILENO, EXIT_NON_NUMERIC_ARG, ft_strlen(EXIT_NON_NUMERIC_ARG));
    write(STDERR_FILENO, "\n", 1);
}

void cmd_exit(t_statement *s)
{
    write(STDOUT_FILENO, "exit\n", 5);
    if (s->argc == 2)
    {
        if (is_all_digits_or_signals(s->argv[1]))
        {
            if (!fits_in_longlong(s->argv[1]))
                exit_non_numeric_arg();
            else
                g_exit_status = ft_atoll(s->argv[1]);
        }
        else
            exit_non_numeric_arg();
    }
    else if (s->argc > 2)
    {
        g_exit_status = EXIT_FAILURE;
        write(STDERR_FILENO, EXIT_TOO_MANY_ARGS, ft_strlen(EXIT_TOO_MANY_ARGS));
        write(STDERR_FILENO, "\n", 1);
    }
    else
        g_exit_status = EXIT_SUCCESS;

    exit(g_exit_status);
}
