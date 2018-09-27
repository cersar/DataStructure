//《算法导论》10.2-8
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int val;
	Node *np = NULL;
}Node;

typedef struct List {
	Node *head = NULL;
	Node *tail = NULL;
}List;

bool isEmpty(List l) {
	if (l.head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

Node *XOR(Node *a, Node *b) {
	return (Node *)(((unsigned long)a ^ ((unsigned long)b)));
}

void Insert(List *l, Node *n) {
	if ((*l).head != NULL) {
		n->np = (*l).head;
		(*l).head->np = XOR((*l).head->np, n);
	}
	else {
		(*l).tail = n;
	}
	(*l).head = n;
}

void Delete(List *l, Node *n) {
	if((*l).head==n)
	{
		//当删除为头节点时，此时prev为NULL，需要特殊处理：
		//改变head的指向，同时更新np
		(*l).head = (*l).head->np;
		(*l).head->np = XOR((*l).head->np, n);
	}
	else {
		Node *p = (*l).head;
		Node *prev = NULL, *tmp;
		while (p != NULL) {
			if (p == n) {
				//更新前一节点的np
				prev->np = XOR(XOR(XOR(prev->np, n), n->np), prev);
				//下一个节点
				tmp = XOR(n->np, prev);
				if (tmp != NULL) {
					//删除的不是尾节点，则更新下一节点的np，由于删除导致其prev改变
					tmp->np = XOR(XOR(tmp->np, n), prev);
				}
				else {
					//删除为尾节点时，则不需要更新下一节点的np，但是需要更新tail的指向
					(*l).tail = prev;
				}
				break;
			}
			tmp = p;
			p = XOR(p->np, prev);
			prev = tmp;
		}
	}
}

//链表反转，时间复杂度O(1)
void Reverse(List *l) {
	Node *tmp=(*l).head;
	(*l).head = (*l).tail;
	(*l).tail = (*l).head;
}

Node *Search(List l,int key) {
	Node *p = l.head;
	Node *prev = NULL, *tmp;
	while (p != NULL&&p->val!=key) {
		tmp = p;
		p = XOR(p->np, prev);
		prev = tmp;
	}
	return p;
}

void printList(List l) {
	Node *p = l.head;
	Node *prev = NULL, *tmp;
	while (p != NULL) {
		printf("%d\t", p->val);
		tmp = p;
		p = XOR(p->np, prev);
		prev = tmp;
	}
	printf("\n");
}

int main() {
	List l;
	Node a = { 1 };
	Node b = { 2 };
	Node c = { 3 };
	Insert(&l, &a);
	Insert(&l, &b);
	Insert(&l, &c);
	printList(l);
	Reverse(&l);
	printList(l);
	Delete(&l, &c);
	printList(l);
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
