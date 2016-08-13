#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node *next;
} Node;

typedef struct Stack {
	Node *head;
} Stack;

void s_push(Stack *stack, int key);
int s_pop(Stack *stack);
int s_peek(Stack *stack);

void s_push(Stack *stack, int key) {
	Node *node = malloc(sizeof(Node));
	node->key = key;
	node->next = stack->head;
	stack->head = node;
}

int s_pop(Stack *stack) {
	Node *node = stack->head;
	stack->head = node->next;
	return node->key;
}

int s_peek(Stack *stack) {
	return stack->head->key;
}

int main() {
	Stack *stack = malloc(sizeof(Stack));
	stack->head = NULL;

	s_push(stack, 15);
	s_push(stack, 23);
	printf("%i\n", s_peek(stack));
	printf("%i\n", s_pop(stack));
	s_push(stack, 45);
	s_push(stack, 65);
	printf("%i\n", s_pop(stack));
	printf("%i\n", s_pop(stack));
	printf("%i\n", s_pop(stack));

}
