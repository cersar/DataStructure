#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10

typedef struct queue {
	int data[MAX_SIZE];
	int head = 0;
	int tail = 0;
}queue;

bool isEmpty(queue *Q) {
	if (Q->head == Q->tail) {
		return true;
	}
	else {
		return false;
	}
}

void Enqueue(queue *Q,int val) {
	if (Q->head == Q->tail + 1 || (Q->head == 0 && Q->tail == MAX_SIZE - 1)) {
		fprintf(stderr, "Queue overflow!!!\n");
	}
	else {
		Q->data[Q->tail] = val;
		if (Q->tail == MAX_SIZE - 1) {
			Q->tail = 0;
		}
		else {
			Q->tail++;
		}
	}
}

int Dequeue(queue *Q) {
	if (Q->head == Q->tail) {
		fprintf(stderr, "Queue underflow!!!\n");
		return -1;
	}
	else {
		int head = Q->data[Q->head];
		if (Q->head == MAX_SIZE - 1) {
			Q->head = 0;
		}
		else {
			Q->head++;
		}
		return head;
	}
}

int main() {
	queue Q;
	printf("队列是否为空？%d\n", isEmpty(&Q));
	Enqueue(&Q, 1);
	Enqueue(&Q, 2);
	Enqueue(&Q, 3);
	Enqueue(&Q, 4);
	Enqueue(&Q, 5);
	Dequeue(&Q);
	Dequeue(&Q);
	Dequeue(&Q);
	Enqueue(&Q, 1);
	Enqueue(&Q, 2);
	Enqueue(&Q, 3);
	while (!isEmpty(&Q)) {
		printf("%d\t", Dequeue(&Q));
	}
	printf("\n");
	Enqueue(&Q, 1);
	Enqueue(&Q, 2);
	Enqueue(&Q, 3);
	while (!isEmpty(&Q)) {
		printf("%d\t", Dequeue(&Q));
	}
	printf("\n");
	return 0;
}
