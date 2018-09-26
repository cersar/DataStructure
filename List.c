#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int val;
	Node *prev=NULL;
	Node *next=NULL;
}*List;

bool isEmpty(List l) {
	if (l == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void Insert(List *l, Node *n) {
	n->next = *l;
	if (*l != NULL) {
		(*l)->prev = n;
	}
	*l = n;
	(*l)->prev = NULL;
}

void Delete(List *l,Node *n) {
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

int main() {
	List l = NULL;
	Node a = {1};
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
	return 0;
}
