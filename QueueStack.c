#include<stdio.h>
#include<stdlib.h>
#include <crtdbg.h> 

typedef struct Node {
	int val;
	Node *next=NULL;
}*SingleList;

typedef struct QueueStack {
	SingleList head=NULL;
	SingleList tail = NULL;
}QueueStack;

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

bool isEmpty(QueueStack S) {
	if (S.head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//尾部插入
void Enqueue(QueueStack *S, int val) {
	Node *n = (Node *)malloc(sizeof(Node));
	n->val = val;
	n->next = NULL;
	if (S->head == NULL) {
		S->head = n;
		S->tail = n;
	}
	else {
		S->tail->next = n;
		S->tail = S->tail->next;
	}

}

//头部删除
int Dequeue(QueueStack *S) {
	Node *n = S->head;
	int val = n->val;
	Delete(&(S->head), n);
	free(n);
	if (S->head == NULL) {
		S->tail = NULL;
	}
	return val;
}

void destory(QueueStack *S) {
	Node *p = S->head, *tmp;
	while (p != NULL) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	S->tail = NULL;
}

int main() {
	QueueStack S;
	Enqueue(&S, 1);
	Enqueue(&S, 2);
	Enqueue(&S, 3);
	while (!isEmpty(S)) {
		int val = Dequeue(&S);
		printf("%d\t", val);
	}
	printf("\n");
	destory(&S);
	_CrtDumpMemoryLeaks();
	return 0;
}
