#include<stdio.h>
#include<string.h>

typedef struct Node {
	int val;
	char *color="BLACK";
	Node *parent = NULL;
	Node *left = NULL;
	Node *right = NULL;
}Node;

typedef struct BRTree {
	Node *root;
	Node *Nil;
}BRTree;

void printTreeInOrder(BRTree t, Node *p) {
	if (p != t.Nil) {
		printTreeInOrder(t, p->left);
		printf("%d--%s  ", p->val, p->color);
		printTreeInOrder(t, p->right);
	}
}

void printTreePreOrder(BRTree t, Node *p) {
	if (p != t.Nil) {
		printf("%d--%s  ", p->val, p->color);
		printTreePreOrder(t, p->left);
		printTreePreOrder(t, p->right);
	}
}

void LeftRotation(BRTree *t, Node *x) {
	Node *y = x->right;
	x->right = y->left;
	if (y->left != t->Nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == t->Nil) {
		t->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RightRotation(BRTree *t, Node *x) {
	Node *y = x->left;
	x->left = y->right;
	if (y->right != t->Nil) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == t->Nil) {
		t->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}

void BRInsertFixup(BRTree *t, Node *z) {
	while (strcmp(z->parent->color, "RED")==0) {
		Node *y = NULL;
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (strcmp(y->color, "RED") == 0) {
				z->parent->color = "BLACK";
				y->color = "BLACK";
				z->parent->parent->color = "RED";
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					LeftRotation(t, z);
				}
				z->parent->color = "BLACK";
				z->parent->parent->color = "RED";
				RightRotation(t, z->parent->parent);
			}
		}
		else {
			y = z->parent->parent->left;
			if (strcmp(y->color, "RED") == 0) {
				z->parent->color = "BLACK";
				y->color = "BLACK";
				z->parent->parent->color = "RED";
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					RightRotation(t, z);
				}
				z->parent->color = "BLACK";
				z->parent->parent->color = "RED";
				LeftRotation(t, z->parent->parent);
			}
		}
		
	}
	t->root->color = "BLACK";
}

void BRInsert(BRTree *t,Node *z) {
	Node *x = t->root;
	Node *y = t->Nil;
	while (x != t->Nil) {
		y = x;
		if (z->val < x->val) {
			x = x->left;
		}
		else x = x->right;
	}
	if (y == t->Nil) {
		t->root = z;
	}
	else if (z->val < y->val) {
		y->left = z;
	}
	else y->right = z;
	z->parent = y;
	z->left = t->Nil;
	z->right = t->Nil;
	z->color = "RED";
	BRInsertFixup(t, z);
}

int main() {
	Node Nil = {0,"BLACK",NULL,NULL,NULL};
	BRTree t = { &Nil,&Nil };
	int a[9] = { 11,2,14,1,7,5,8,15,4};
	Node nodes[9];
	for (int i = 0; i < 9; ++i) {
		nodes[i].val = a[i];
		BRInsert(&t, &nodes[i]);
		printf("中序:\t");
		printTreeInOrder(t, t.root);
		printf("\n");
		printf("先序:\t");
		printTreePreOrder(t, t.root);
		printf("\n");
	}
	return 0;
}
