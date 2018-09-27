#include<stdio.h>
#include<stdlib.h>
#include <crtdbg.h> 

typedef struct Node {
	int val;
	Node *next=NULL;
}*SingleList;

typedef struct ListStack {
	SingleList L=NULL;
}ListStack;

void Insert(SingleList *l, Node *n) {
	if (*l != NULL) {
		n->next = (*l);
	}
	*l = n;
}

//常规实现，时间复杂度O(n)
void Delete(SingleList *l,Node *n) {
	if (*l == n) {
		*l = n->next;
	}
	else {
		Node *prev = *l;
		Node *p = (*l)->next;
		while (p != NULL) {
			if (p == n) {
				prev->next = n->next;
				break;
			}
			prev = p;
			p = p->next;
		}
	}
}

//常规实现，非尾元素时间复杂度O(1)，尾元素时间复杂度O(n)
void DeleteLinear(SingleList *l, Node *n) {
	if (n->next!=NULL) {
		n->val = n->next->val;
		n->next = n->next->next;
	}
	else {
		Node *prev = *l;
		Node *p = (*l)->next;
		while (p != NULL) {
			if (p == n) {
				prev->next = n->next;
				break;
			}
			prev = p;
			p = p->next;
		}
	}
}

Node * Search(SingleList *l,int k) {
	Node *p = *l;
	while (p != NULL&&p->val != k) {
		p = p->next;
	}
	return p;
}

bool isEmpty(ListStack S) {
	if (S.L == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void push(ListStack *S, int val) {
	Node *n = (Node *)malloc(sizeof(Node));
	n->val = val;
	n->next = NULL;
	Insert(&(S->L), n);
}

int pop(ListStack *S) {
	Node *n = S->L;
	int val = n->val;
	Delete(&(S->L), n);
	free(n);
	return val;
}

void destory(ListStack *S) {
	Node *p = S->L, *tmp;
	while (p != NULL) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
}

int main() {
	ListStack S;
	push(&S, 1);
	push(&S, 2);
	push(&S, 3);
	while (!isEmpty(S)) {
		int val = pop(&S);
		printf("%d\t", val);
	}
	printf("\n");
	destory(&S);
	_CrtDumpMemoryLeaks();
	return 0;
}
