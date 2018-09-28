#include<stdio.h>
#include<stdlib.h>
#include <crtdbg.h> 
#define HASESIZE 7

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


Node * Search(SingleList l, int k) {
	Node *p = l;
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

void printList(SingleList l) {
	Node *p = l;
	while (p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
}

int hash(int v) {
	return v%HASESIZE;
}

//hash表插入
void HashInsert(SingleList *Dict,int key) {
	Insert(&Dict[hash(key)], key);
}
//hash表查找
bool HashSearch(SingleList *Dict, int key) {
	Node *r =  Search(Dict[hash(key)], key);
	if (r != NULL) {
		return true;
	}
	else {
		return false;
	}
}
//hash表删除
void HashDelete(SingleList *Dict, int key) {
	Delete(&Dict[hash(key)], key);
}
//hash表内存释放
void DestoryHash(SingleList *Dict) {
	for (int i = 0; i < HASESIZE; ++i) {
		Destory(&Dict[i]);
	}
}
//hash表打印
void PrintHash(SingleList *Dict) {
	for (int i = 0; i < HASESIZE; ++i) {
		if (Dict[i] != NULL) {
			printf("DictKey=%d，Vals: ",i);
			printList(Dict[i]);
		}
	}
}


int main() {
	SingleList Dict[HASESIZE] = {0};
	HashInsert(Dict, 1);
	HashInsert(Dict, 2);
	HashInsert(Dict, 3);
	HashInsert(Dict, 10);
	HashInsert(Dict, 8);
	HashInsert(Dict, 15);
	PrintHash(Dict);
	int key = 8;
	if (HashSearch(Dict, key)) {
		printf("存在键值为%d的元素.\n", key);
	}
	else {
		printf("不存在键值为%d的元素.\n", key);
	}
	HashDelete(Dict, key);
	PrintHash(Dict);
	if (HashSearch(Dict, key)) {
		printf("存在键值为%d的元素.\n", key);
	}
	else {
		printf("不存在键值为%d的元素.\n", key);
	}
	DestoryHash(Dict);
	_CrtDumpMemoryLeaks();
	return 0;
}
