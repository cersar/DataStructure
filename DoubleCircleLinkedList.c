//不使用哨兵实现的双向循环链表
#include <iostream>
#include <crtdbg.h>

using namespace std;

typedef struct Node {
	int val;
	Node *next;
	Node *prev;
}*DoubleCircleLinkedList;

void ListInsert(DoubleCircleLinkedList *l,int val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->val = val;
	if (*l == NULL) {
		p->prev = p;
		p->next = p;
	}
	else {
		p->prev = (*l)->prev;
		(*l)->prev->next = p;
		(*l)->prev = p;
		p->next = *l;
	}
	*l = p;
}

void ListDelete(DoubleCircleLinkedList *l,Node *p) {
	if (p == *l) {
		if (p->next != p) {
			(*l) = p->next;
		}
		else {
			(*l) = NULL;
		}
		
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}

void printNode(Node *p) {
	if (p != NULL) {
		printf("val=%d\n", p->val);
	}
}

void printList(DoubleCircleLinkedList l) {
	if (l != NULL) {
		Node *p = l;
		do {
			printNode(p);
			p = p->next;
		} while (p != l);
	}
}

void FreeMemory(DoubleCircleLinkedList *l) {
	if (*l != NULL) {
		Node *p = *l, *tmp = NULL;
		do{
			tmp = p->next;
			free(p);
			p = tmp;
		} while (p != *l);
		*l = NULL;
	}
	
}
