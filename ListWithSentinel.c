#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int val;
	Node *prev=NULL;
	Node *next=NULL;
}Node;

typedef struct List {
	Node nil = {0,&nil,&nil};
}List;

void Insert(List *l, Node *n) {
	n->next = (*l).nil.next;
	(*l).nil.next->prev = n;
	(*l).nil.next = n;
	n->prev = &(*l).nil;
}

void Delete(List *l,Node *n) {
	n->prev->next = n->next;
	n->next->prev = n->prev;
}

Node * Search(List *l,int k) {
	Node *p = (*l).nil.next;
	while (p != &(*l).nil&&p->val != k) {
		p = p->next;
	}
	return p;
}
//search的另一版本
Node * Search2(List *l, int k) {
	Node *p = (*l).nil.next;
	(*l).nil.val = k;
	while (p->val != k) {
		p = p->next;
	}
	return p;
}

int main() {
	List l;
	Node a = {1};
	Node b = { 2 };
	Node c = { 3 };
	Insert(&l, &a);
	Insert(&l, &b);
	Insert(&l, &c);
	Node *p = l.nil.next;
	while (p != &l.nil) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	Delete(&l, &b);
	p = l.nil.next;
	while (p != &l.nil) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	Node *r = Search(&l, 2);
	if (r != &l.nil) {
		printf("找到元素:%d\n", r->val);
	}
	else {
		printf("未找到这样的元素！\n");
	}
	r = Search(&l, 3);
	if (r != &l.nil) {
		printf("找到元素:%d\n", r->val);
	}
	else {
		printf("未找到这样的元素！\n");
	}
	return 0;
}
