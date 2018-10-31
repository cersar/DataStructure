//双向链表
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int val;
	Node *prev = NULL;
	Node *next = NULL;
}*DoubleLinkedList;

bool isEmpty(DoubleLinkedList l) {
	if (l == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void Insert(DoubleLinkedList *l, Node *n) {
	n->next = *l;
	if (*l != NULL) {
		(*l)->prev = n;
	}
	*l = n;
	(*l)->prev = NULL;
}

void Delete(DoubleLinkedList *l, Node *n) {
	if (n->prev != NULL) {
		n->prev->next = n->next;
	}
	else {
		*l = n->next;
	}
	if (n->next != NULL) {
		n->next->prev = n->prev;
	}
}

Node * Search(DoubleLinkedList l, int k) {
	Node *p = l;
	while (p != NULL && p->val != k) {
		p = p->next;
	}
	return p;
}

int main() {
	DoubleLinkedList l = NULL;
	Node a = { 1 };
	Node b = { 2 };
	Node c = { 3 };
	Insert(&l, &a);
	Insert(&l, &b);
	Insert(&l, &c);
	Node *p = l;
	while (p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	Delete(&l, &b);
	p = l;
	while (p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	Node *r = Search(l, 2);
	if (r != NULL) {
		printf("找到元素:%d\n", r->val);
	}
	else {
		printf("未找到这样的元素！\n");
	}
	r = Search(l, 3);
	if (r != NULL) {
		printf("找到元素:%d\n", r->val);
	}
	else {
		printf("未找到这样的元素！\n");
	}
	return 0;
}
