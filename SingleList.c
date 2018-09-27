#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int val;
	Node *next = NULL;
}*SingleList;

void Insert(SingleList *l, Node *n) {
	if (*l != NULL) {
		n->next = (*l);
	}
	*l = n;
}

//常规实现，时间复杂度O(n)
void Delete(SingleList *l, Node *n) {
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
	if (n->next != NULL) {
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

Node * Search(SingleList *l, int k) {
	Node *p = *l;
	while (p != NULL&&p->val != k) {
		p = p->next;
	}
	return p;
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
	Reverse(&l);
	p = l;
	while (p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	DeleteLinear(&l, &b);
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
	return 0;
}
