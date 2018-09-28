#include<stdio.h>
#include<stdlib.h>
#include <crtdbg.h> 

typedef struct Node {
	int val;
	Node *next = NULL;
}*SingleList;

void Insert(SingleList *l, int key) {
	Node *n = (Node *)malloc(sizeof(Node));
	n->val = key;
	n->next = NULL;
	if (*l != NULL) {
		n->next = (*l);
	}
	*l = n;
}

//常规实现，时间复杂度O(n)
void Delete(SingleList *l, int key) {
	if ((*l)->val == key) {
		Node *tmp = *l;
		*l = (*l)->next;
		free(tmp);
	}
	else {
		Node *prev = *l;
		Node *p = (*l)->next;
		while (p != NULL) {
			if (p->val == key) {
				prev->next = p->next;
				free(p);
				break;
			}
			prev = p;
			p = p->next;
		}
	}
}


Node * Search(SingleList *l, int k) {
	Node *p = *l;
	while (p != NULL&&p->val != k) {
		p = p->next;
	}
	return p;
}

void Destory(SingleList *l) {
	Node *p = *l,*tmp;
	while (p != NULL) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	(*l) = NULL;
}

//链表反转
void Reverse(SingleList *l) {
	if ((*l) != NULL) {
		Node *prev = *l;
		Node *p = (*l)->next;
		Node *tmp = NULL;
		//第一个节点反转
		(*l)->next = NULL;
		//余下节点反转
		while (p != NULL) {
			tmp = p->next;
			p->next = prev;
			prev = p;
			p = tmp;
		}
		(*l) = prev;
	}
}

int main() {
	SingleList l = NULL;
	Insert(&l, 1);
	Insert(&l, 2);
	Insert(&l, 3);
	Node *p = l;
	while (p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	Reverse(&l);
	p = l;
	while (p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	Delete(&l, 1);
	p = l;
	while (p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	Node *r = Search(&l, 2);
	if (r != NULL) {
		printf("找到元素:%d\n", r->val);
	}
	else {
		printf("未找到这样的元素！\n");
	}
	r = Search(&l, 3);
	if (r != NULL) {
		printf("找到元素:%d\n", r->val);
	}
	else {
		printf("未找到这样的元素！\n");
	}
	Destory(&l);
	_CrtDumpMemoryLeaks();
	return 0;
}
