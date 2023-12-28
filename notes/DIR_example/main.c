/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:06:02 by atucci            #+#    #+#             */
/*   Updated: 2023/12/28 10:18:01 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>

int	main(void)
{
	DIR				*directory;
	struct dirent	*entry;

	directory = opendir(".");
	if (directory == NULL)
		return (perror("Error opening directory"), 1);
	entry = readdir(directory);
	while (entry != NULL)
	{
		printf("%s\n", entry->d_name);
		entry = readdir(directory);
	}
	if (closedir(directory) == -1)
		return (perror("Error closing directory"), 1);
	return (0);
}
