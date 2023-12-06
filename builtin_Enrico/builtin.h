/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:13:11 by enricogiral       #+#    #+#             */
/*   Updated: 2023/12/05 17:43:46 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

#include "minishell.h"

// Dichiarazioni delle funzioni per i comandi built-in
int minishell_echo(char **args);
int minishell_cd(char **args);
int minishell_pwd(void);
int minishell_export(char **args, t_env **env_list);
int minishell_unset(char **args, t_env **env_list);
int minishell_env(t_env *env_list);

#endif
