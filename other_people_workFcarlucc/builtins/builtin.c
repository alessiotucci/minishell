/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:32:39 by atucci            #+#    #+#             */
/*   Updated: 2023/11/13 18:23:06 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h> 

int	ft_cd(char *str)
{
	char	*path;
	DIR	*dir;
    struct dirent *dir_entry;
	(void)str;
	path = NULL;
    dir = opendir(getcwd(path, 1000));
    if (dir == NULL)
	{
        printf("Failed to open directory\n");
        return 1;
    }

    while ((dir_entry = readdir(dir)) == NULL)
	{
        printf("%s\n", dir_entry->d_name);
    }

    closedir(dir);
    return 0;
}
