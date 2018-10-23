#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#define BLACK 0
#define RED 1

typedef struct TreeNode {
	int key;
	int val;
	int color;
	TreeNode *p;
	TreeNode *left;
	TreeNode *right;
}TreeNode, *RBTree;

bool isRed(TreeNode *x) {
	if (x != NULL && x->color == RED) {
		return true;
	}
	return false;
}

void LeftRotation(RBTree *t,TreeNode *x) {
	TreeNode *y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->p = x;
	}
	y->p = x->p;
	if (x->p == NULL) {
		*t = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else if (x == x->p->right) {
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

void RightRotation(RBTree *t, TreeNode *x) {
	TreeNode *y = x->left;
	x->left = y->right;
	if (y->right != NULL) {
		y->right->p = x;
	}
	y->p = x->p;
	if (x->p == NULL) {
		*t = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else if (x == x->p->right) {
		x->p->right = y;
	}
	y->right = x;
	x->p = y;
}

void RBInsertFixup(RBTree *t,TreeNode *x) {
	TreeNode *y = NULL;
	while (isRed(x->p)) {
		y = x->p->p;
		if (x->p == y->left) {
			if (isRed(y->right)) {
				y->color = RED;
				x->p->color = BLACK;
				y->right->color = BLACK;
				x = y;
			}
			else {
				if (x == x->p->right) {
					x = x->p;
					LeftRotation(t, x);
				}
				RightRotation(t, y);
				x->p->color = BLACK;
				y->color = RED;
			}
		}
		else {
			if (isRed(y->left)) {
				y->color = RED;
				x->p->color = BLACK;
				y->left->color = BLACK;
				x = y;
			}
			else {
				if (x == x->p->left) {
					x = x->p;
					RightRotation(t, x);
				}
				LeftRotation(t, y);
				x->p->color = BLACK;
				y->color = RED;
			}
		}
	}
	(*t)->color = BLACK;
}

void RBInsert(RBTree *t,int key,int val) {
	TreeNode *p = NULL;
	TreeNode *x = *t;
	while (x != NULL) {
		p = x;
		if (key < x->key) {
			x = x->left;
		}
		else if (key > x->key) {
			x = x->right;
		}
		else {
			x->val = val;
			return ;
		}
	}
	x = (TreeNode *)malloc(sizeof(TreeNode));
	x->key = key;
	x->val = val;
	x->color = RED;
	x->left = NULL;
	x->right = NULL;
	x->p = p;
	if (p == NULL) {
		*t = x;
	}
	else if (key < p->key) {
		p->left = x;
	}
	else if (key > p->key) {
		p->right = x;
	}
	RBInsertFixup(t, x);

}

void printNode(TreeNode *n) {
	if (n != NULL) {
		printf("[key=%d,value=%d,color=%d]\n", n->key, n->val, n->color);
	}
}

void printInOrder(RBTree t) {
	if (t != NULL) {
		printInOrder(t->left);
		printNode(t);
		printInOrder(t->right);
	}
}

void printPreOrder(RBTree t) {
	if (t != NULL) {
		printNode(t);
		printPreOrder(t->left);
		printPreOrder(t->right);
	}
}

void FreeMemory(RBTree t) {
	if (t != NULL) {
		FreeMemory(t->left);
		FreeMemory(t->right);
		free(t);
	}
}

TreeNode *TreeMininum(RBTree t) {
	TreeNode *p = NULL;
	while (t != NULL) {
		p = t;
		t = t->left;
	}
	return p;
}

void TreeTransplant(RBTree *t, TreeNode *x, TreeNode *y) {
	if (y != NULL) {
		y->p = x->p;
	}
	if (x->p == NULL) {
		*t = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else if (x == x->p->right) {
		x->p->right = y;
	}
}

void RBDeleteFixup(RBTree *t, TreeNode *x, TreeNode *p) {
	TreeNode *y = NULL;
	while (x != *t && !isRed(x)) {
		if (x == p->left) {
			y = p->right;
			if (y->color == RED) {
				p->color = RED;
				y->color = BLACK;
				LeftRotation(t,p);
				y = p->right;
			}
			if (!isRed(y->left) && !isRed(y->right)) {
				y->color = RED;
				x = p;
				p = p->p;
			}
			else {
				if (isRed(y->left)) {
					y->left->color = BLACK;
					y->color = RED;
					RightRotation(t,y);
					y = p->right;
				}
				y->right->color = BLACK;
				y->color = p->color;
				p->color = BLACK;
				LeftRotation(t,p);
				x = *t;
			}
		}
		else {
			y = p->left;
			if (y->color == RED) {
				p->color = RED;
				y->color = BLACK;
				RightRotation(t, p);
				y = p->left;
			}
			if (!isRed(y->left) && !isRed(y->right)) {
				y->color = RED;
				x = p;
				p = p->p;
			}
			else {
				if (isRed(y->right)) {
					y->right->color = BLACK;
					y->color = RED;
					LeftRotation(t, y);
					y = p->left;
				}
				y->color = p->color;
				p->color = BLACK;
				RightRotation(t, p);
				x = *t;
			}
		}
	}
	x->color = BLACK;
}

void TreeDelete(RBTree *t, int val) {
	TreeNode *x = *t;
	while (x != NULL) {
		if (val < x->val) {
			x = x->left;
		}
		else if (val > x->val) {
			x = x->right;
		}
		else {
			TreeNode *z = NULL;//记录删除或移动节点的孩子
			TreeNode *p = NULL;//记录删除或移动后z的父亲节点，由于z可能为NULL，所以需单独记录
			int color = 0;//记录删除或者内部移动节点的颜色
			if (x->left == NULL) {
				p = x->p;
				z = x->right;
				color = x->color;
				TreeTransplant(t, x, x->right);
			}
			else if (x->right == NULL) {
				p = x->p;
				z = x->left;
				color = x->color;
				TreeTransplant(t, x, x->left);
			}
			else {
				TreeNode *y = TreeMininum(x->right);
				z = y->right;
				color = y->color;
				if (y->p == x) {
					//y是x的孩子节点
					p = y;
				}
				else {
					p = y->p;
					TreeTransplant(t, y, y->right);
					y->right = x->right;
					x->right->p = y;
				}
				TreeTransplant(t, x, y);
				y->left = x->left;
				x->left->p = y;
				y->color = x->color;
			}
			if (color == BLACK) {
				RBDeleteFixup(t, z, p);
			}
			free(x);
			break;
		}
	}
}

int main()
{
	RBTree t = NULL;
	for (int i = 0; i < 10; i++) {
		RBInsert(&t, i, i);
	}
	TreeDelete(&t, 5);
	TreeDelete(&t, 8);
	RBInsert(&t, 5, 5);
	TreeDelete(&t, 3);
	TreeDelete(&t, 4);
	TreeDelete(&t, 0);
	RBInsert(&t, 3, 3);
	RBInsert(&t, 4, 4);
	printf("删除前:\n");
	printPreOrder(t);
	TreeDelete(&t, 5);
	printf("删除后:\n");
	printPreOrder(t);
	FreeMemory(t);
	_CrtCheckMemory();
	system("pause");
	return 0;
}
