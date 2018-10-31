//使用哨兵实现的双向循环链表
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int val;
	Node *prev = NULL;
	Node *next = NULL;
}Node;

typedef struct List {
	Node nil = { 0,&nil,&nil };
}List;

void Insert(List *l, Node *n) {
	n->next = (*l).nil.next;
	(*l).nil.next->prev = n;
	(*l).nil.next = n;
	n->prev = &(*l).nil;
}

void Delete(List *l, Node *n) {
	n->prev->next = n->next;
	n->next->prev = n->prev;
}

Node * Search(List *l, int k) {
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

//链表合并O(1)
//l1、l2合并到新链表l,由于原l1、l2的结构已经被破坏，最后将链表置空
void Union(List *l1, List *l2,List *l) {
	(*l).nil.next = (*l1).nil.next;
	(*l1).nil.next->prev = &(*l).nil;
	(*l).nil.prev = (*l2).nil.prev;
	(*l2).nil.prev->next = &(*l).nil;
	(*l1).nil.prev->next = (*l2).nil.next;
	(*l2).nil.next->prev = (*l1).nil.prev;
	(*l1).nil.next = NULL;
	(*l2).nil.next = NULL;
}

int main() {
	List l1,l2,l;
	Node a = { 1 };
	Node b = { 2 };
	Node c = { 3 };
	Node d = { 4 };
	Node e = { 5 };
	Node f = { 6 };
	Insert(&l1, &a);
	Insert(&l1, &b);
	Insert(&l1, &c);
	Insert(&l2, &d);
	Insert(&l2, &e);
	Insert(&l2, &f);
	Union(&l1, &l2, &l);
	Node *p = l.nil.next;
	while (p != &l.nil) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	return 0;
}
