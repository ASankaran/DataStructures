#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *head;
	Node *tail;
} Queue;

void q_enqueue(Queue *queue, int key);
int q_dequeue(Queue *queue);

void q_enqueue(Queue *queue, int key) {
	if (queue->head == NULL) {
		Node *node = malloc(sizeof(Node));
		node->key = key;
		node->next = NULL;
		queue->head = node;
		queue->tail = node;
		return;
	}
	Node *node = malloc(sizeof(Node));
	node->key = key;
	node->next = NULL;
	queue->tail->next = node;
	queue->tail = node;
}

int q_dequeue(Queue *queue) {
	if (queue->head == NULL) {
		return 0;
	}
	Node *node = queue->head;
	queue->head = node->next;
	return node->key;
}

int main() {
	Queue *queue = malloc(sizeof(Queue));
	queue->head = NULL;
	q_enqueue(queue, 5);
	q_enqueue(queue, 7);
	printf("%i\n", q_dequeue(queue));
	q_enqueue(queue, 4);
	q_enqueue(queue, 9);
	printf("%i\n", q_dequeue(queue));
	printf("%i\n", q_dequeue(queue));
	printf("%i\n", q_dequeue(queue));
}
