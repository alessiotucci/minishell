/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:37:25 by atucci            #+#    #+#             */
/*   Updated: 2023/12/18 15:07:26 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	print_tabs(int num_of_tabs)
{
	int		count;
	char	tab = '\t';
	count = 0;
	while (count < num_of_tabs)
	{
		write(1, &tab, 1);
		count++;
	}
}
int	print_tree(t_tree_node *root, int depth)
{
	if (root == NULL)
	{
		print_tabs(depth);
		return (printf("null"));
	}
	print_tabs(depth);
	printf("\t[ %s ]\n", root->token->command_as_string);
	printf("LEFT:");
	print_tree(root->left, depth + 1);
	printf("\tRIGHT: ");
	print_tree(root->right, depth + 1);
	return (0);
}

void	parser2(void)
{
	return ;
}

void	parser3(void)
{
	return ;
}

void	free_tree(t_tree_node *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	free(node);
}
