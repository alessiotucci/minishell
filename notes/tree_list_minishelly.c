/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stocazzo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:35:45 by atucci            #+#    #+#             */
/*   Updated: 2023/12/17 17:45:50 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct list_node
{
	int					priority_level;
	char				*cmd_as_string;
	struct list_node	*next;
	struct list_node	*prev;
}	list_node;

typedef struct tree_node
{
	int					priority_level;
	char				*cmd_as_string;
	struct tree_node	*left;
	struct tree_node	*right;
}	tree_node;

/*this function create a single node of a tree*/
tree_node*	createtree_node(int priority_level, char *string)
{
	tree_node *new_node;

	new_node = (tree_node*)malloc(sizeof(tree_node));
	new_node->cmd_as_string = string;
	new_node->priority_level = priority_level;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

/*this function create a tree from a list*/
tree_node*	create_tree_list(list_node *head)
{
	if (head == NULL)
		return NULL;
	list_node *high_priority = head;
	list_node *curr_node = head;
	while (curr_node != NULL) // first while, check for high priority
	{
		if (curr_node->priority_level > high_priority->priority_level)
			high_priority = curr_node;
		curr_node = curr_node->next;
	}
	// the first tree_node will be the one with the highest priority
	tree_node *root = createtree_node(high_priority->priority_level, high_priority->cmd_as_string);
	list_node *head1 = NULL;
	list_node *head2 = NULL;
	// re-setting the current node to the head
	curr_node = head;
	while (curr_node != high_priority)
	{
		list_node *new_node = (list_node*)malloc(sizeof(list_node));
		new_node->cmd_as_string = curr_node->cmd_as_string; // Add this line
		new_node->priority_level = curr_node->priority_level;
		new_node->next = head1;
		head1 = new_node;
		curr_node = curr_node->next;
	}
	curr_node = high_priority->next;
	while (curr_node != NULL)
	{
	list_node *new_node = (list_node*)malloc(sizeof(list_node));
	new_node->cmd_as_string = curr_node->cmd_as_string; // Add this line
	new_node->priority_level = curr_node->priority_level;
	new_node->next = head2;
	head2 = new_node;
	curr_node = curr_node->next;
	}
	root->left = create_tree_list(head1);
	root->right = create_tree_list(head2);
	return (root);
}


int	main()
{
	//first node
	list_node *head = (list_node*)malloc(sizeof(list_node));
	head->priority_level = 1;
	head->cmd_as_string = "pwd";
	head->prev = NULL;
	//second node
	list_node *second_node = (list_node*)malloc(sizeof(list_node));
	second_node->cmd_as_string = "ls";
	second_node->priority_level = 2;
	second_node->prev = head;
	//third node
	list_node *third_node = (list_node*)malloc(sizeof(list_node));
	third_node->cmd_as_string = "echo";
	third_node->priority_level = 3;
	third_node->prev = second_node;
	head->next = second_node;
	second_node->next = third_node;
	third_node->next = NULL;
	// lastly we create a tree starting from the linked list
	tree_node *root = create_tree_list(head);
	return 0;
}
