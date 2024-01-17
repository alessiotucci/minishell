#include <stdio.h>
#include <stdlib.h>

typedef struct t_list_of_tok
{
	char *token;
	struct t_list_of_tok *next;
	struct t_list_of_tok *previous;
} t_list_of_tok;

// Insert your move_node function here
void move_node(t_list_of_tok **head, t_list_of_tok *target_node, t_list_of_tok *moving_node)
{
	t_list_of_tok *temp = NULL;

	// If the moving node is the head of the list, update the head pointer
	if (*head == moving_node)
		*head = moving_node->next;
	// Disconnect the moving node and all nodes after it from the list
	if (moving_node->previous != NULL)
		moving_node->previous->next = NULL;

	// Find the last node in the moving node's sublist
	temp = moving_node;
	while (temp->next != NULL)
		temp = temp->next;
	// If the target node is the head of the list, move the moving node to the front
	if (*head == target_node)
	{
		temp->next = *head;
		(*head)->previous = temp;
		*head = moving_node;
	}
	else
	{
		// Otherwise, insert the moving node before the target node
		temp->next = target_node;
		moving_node->previous = target_node->previous;
		target_node->previous->next = moving_node;
		target_node->previous = temp;
	}
}

int main()
{
	// Create nodes
	t_list_of_tok *node1 = malloc(sizeof(t_list_of_tok));
	t_list_of_tok *node2 = malloc(sizeof(t_list_of_tok));
	t_list_of_tok *node3 = malloc(sizeof(t_list_of_tok));

	// Initialize nodes
	node1->token = ">";
	node1->next = node2;
	node1->previous = NULL;

	node2->token = "filename";
	node2->next = node3;
	node2->previous = node1;

	node3->token = "pwd";
	node3->next = NULL;
	node3->previous = node2;

	// Set head of list
	t_list_of_tok *head = node1;
	printf("before\n");
	t_list_of_tok *tempo = head;
	while (tempo != NULL)
	{
		printf("%s ", tempo->token);
		tempo = tempo->next;
	}
	printf("\n\n");

	// Move node3 before node1
	move_node(&head, node1, node3);
	printf("after\n");
	// Print list
	t_list_of_tok *temp = head;
	while (temp != NULL)
	{
		printf("%s ", temp->token);
		temp = temp->next;
	}
	printf("\n");

	// Free memory
	free(node1);
	free(node2);
	free(node3);

	return 0;
}
