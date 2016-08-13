#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct LinkedList {
	Node *head;
} LinkedList;

void ll_traverse(LinkedList *list);
void ll_traversenode(Node *node);
void ll_insert(LinkedList *list, int key);
void ll_insertnode(Node *current, int key);
Node * ll_find(LinkedList *list, int key);
Node * ll_findnode(Node *node, int key);
void ll_remove(LinkedList *list, int key);
void ll_removenode(Node *node);

void ll_traverse(LinkedList *list) {
	if (list->head != NULL) {
		ll_traversenode(list->head);
	}
}

void ll_traversenode(Node *node) {
	if (node != NULL) {
		printf("%i\n", node->key);
		ll_traversenode(node->next);
	}
}

void ll_insert(LinkedList *list, int key) {
	if (list->head == NULL) {
		Node *node = malloc(sizeof(Node));
		node->key = key;
		node->prev = NULL;
		node->next = NULL;
		list->head = node;
		return;
	}
	ll_insertnode(list->head, key);
}

void ll_insertnode(Node *current, int key) {
	if (current->next == NULL) {
		Node *node = malloc(sizeof(Node));
		node->key = key;
		node->prev = current;
		node->next = NULL;
		current->next = node;
		return;
	}
	ll_insertnode(current->next, key);
}

Node * ll_find(LinkedList *list, int key) {
	return list->head == NULL ? NULL : ll_findnode(list->head, key);
}

Node * ll_findnode(Node *node, int key) {
	if (node == NULL) {
		return NULL;
	} else if (node->key == key) {
		return node;
	} else {
		return ll_findnode(node->next, key);
	}
}

void ll_remove(LinkedList *list, int key) {
	if (list->head == NULL) {
		return;
	} else if (list->head->key == key) {
		list->head = list->head->next;
	} else {
		ll_removenode(ll_find(list, key));
	}
}

void ll_removenode(Node *node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
}

int main() {
	LinkedList *list = malloc(sizeof(LinkedList));
	list->head = NULL;

	ll_insert(list, 10);
	ll_insert(list, 35);
	ll_insert(list, 2);
	ll_insert(list, 22);

	ll_traverse(list);
	printf("-------\n");

	ll_remove(list, 10);
	ll_remove(list, 2);

	ll_traverse(list);
	printf("-------\n");
}
