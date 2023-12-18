/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stocazzo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:35:45 by atucci            #+#    #+#             */
/*   Updated: 2023/12/18 08:32:39 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// Define a structure for list nodes
typedef struct list_node
{
	int					priority_level; // Priority level of the command
	char				*cmd_as_string; // Command as a string
	struct list_node	*next;
	struct list_node	*prev;
}	list_node;

// Define a structure for tree nodes
typedef struct tree_node
{
	int					priority_level; // Priority level of the command
	char				*cmd_as_string; // Command as a string
	struct tree_node	*left;
	struct tree_node	*right;
}	tree_node;

// Function to create a new tree node
tree_node*	createtree_node(int priority_level, char *string)
{
	tree_node *new_node;

	new_node = (tree_node*)malloc(sizeof(tree_node)); // Allocate memory for the new node
	new_node->cmd_as_string = string;
	new_node->priority_level = priority_level;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node); // Return the new node
}

// Function to create a binary tree from a linked list
tree_node*	create_tree_list(list_node *head)
{
	if (head == NULL) // If the list is empty, return NULL
		return NULL;
	list_node *high_priority = head; // Initialize the highest priority node as the head of the list
	list_node *curr_node = head; // Initialize the current node as the head of the list
	while (curr_node != NULL) // Traverse the list to find the node with the highest priority
	{
		if (curr_node->priority_level > high_priority->priority_level) // If the current node has a higher priority than the highest priority node
			high_priority = curr_node; // Update the highest priority node
		curr_node = curr_node->next; // Move to the next node
	}
	// Create a new tree node with the highest priority node's priority level and command string
	tree_node *root = createtree_node(high_priority->priority_level, high_priority->cmd_as_string);

	list_node *head1 = NULL; // Initialize the head of the first sublist
	list_node *head2 = NULL; // Initialize the head of the second sublist
	curr_node = head; // Reset the current node to the head of the list
	while (curr_node != high_priority) // Traverse the list until the highest priority node
	{
		list_node *new_node = (list_node*)malloc(sizeof(list_node));
		new_node->cmd_as_string = curr_node->cmd_as_string;
		new_node->priority_level = curr_node->priority_level;
		new_node->next = head1;
		head1 = new_node;
		curr_node = curr_node->next;
	}
	curr_node = high_priority->next; // Set the current node to the node after the highest priority node
	while (curr_node != NULL) // Traverse the rest of the list
	{
		list_node *new_node = (list_node*)malloc(sizeof(list_node));
		new_node->cmd_as_string = curr_node->cmd_as_string;
		new_node->priority_level = curr_node->priority_level;
		new_node->next = head2;
		head2 = new_node;
		curr_node = curr_node->next;
	}
	root->left = create_tree_list(head1); // Recursively create the left subtree from the first sublist
	root->right = create_tree_list(head2); // Recursively create the right subtree from the second sublist
	return (root); // Return the root of the tree
}

int	main()
{
	// Create the first node of the list
	list_node *head = (list_node*)malloc(sizeof(list_node));
	head->priority_level = 1;
	head->cmd_as_string = "pwd";
	head->prev = NULL;

	// Create the second node of the list
	list_node *second_node = (list_node*)malloc(sizeof(list_node));
	second_node->cmd_as_string = "ls";
	second_node->priority_level = 2;
	second_node->prev = head;

	// Create the third node of the list
	list_node *third_node = (list_node*)malloc(sizeof(list_node));
	third_node->cmd_as_string = "echo";
	third_node->priority_level = 3;
	third_node->prev = second_node;

	// Link the nodes to form the list
	head->next = second_node;
	second_node->next = third_node;
	third_node->next = NULL;

	// Create a binary tree from the linked list
	tree_node *root = create_tree_list(head);

	return 0; // Return 0 to indicate successful execution
}

