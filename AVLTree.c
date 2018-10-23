#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

typedef struct TreeNode {
	int key;
	int val;
	int hight;
	TreeNode *p;
	TreeNode *left;
	TreeNode *right;
}TreeNode, *AVLTree;

int Max(int a, int b) {
	return a > b ? a : b;
}

int Hight(TreeNode *x) {
	if (x == NULL) {
		return 0;
	}
	else {
		return x->hight;
	}
}

void UpdateHight(TreeNode *x) {
	if (x != NULL) {
		x->hight = Max(Hight(x->left), Hight(x->right)) + 1;
	}
}

void LeftRotation(AVLTree *t,TreeNode *x) {
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
	UpdateHight(x);
	UpdateHight(y);

}

void RightRotation(AVLTree *t, TreeNode *x) {
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
	UpdateHight(x);
	UpdateHight(y);
}

void Balance(AVLTree *t,TreeNode *x) {
	int cnt = 0;
	while (x!=NULL) {
		if (Hight(x->left) < Hight(x->right) - 1) {
			if (Hight(x->right->right) < Hight(x->right->left)) {
				RightRotation(t, x->right);
				cnt++;
			}
			LeftRotation(t,x);
			cnt++;
		}
		else if (Hight(x->left) > Hight(x->right) + 1) {
			if (Hight(x->left->left) < Hight(x->left->right)) {
				LeftRotation(t, x->left);
				cnt++;
			}
			RightRotation(t, x);
			cnt++;
		}
		else {
			UpdateHight(x);
		}
		x = x->p;
		printf("旋转%d次\n",cnt);
	}
}

void AVLInsert(AVLTree *t,int key,int val) {
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
	Balance(t, x);
}

TreeNode *TreeMininum(AVLTree t) {
	TreeNode *p = NULL;
	while (t != NULL) {
		p = t;
		t = t->left;
	}
	return p;
}

void TreeTransplant(AVLTree *t, TreeNode *x, TreeNode *y) {
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


void TreeDelete(AVLTree *t, int val) {
	TreeNode *x = *t;
	while (x != NULL) {
		if (val < x->val) {
			x = x->left;
		}
		else if (val > x->val) {
			x = x->right;
		}
		else {
			TreeNode *z = NULL;//记录删除或移动后替换到该位置的节点
			if (x->left == NULL) {
				z = x->p;
				TreeTransplant(t, x, x->right);
			}
			else if (x->right == NULL) {
				z = x->p;
				TreeTransplant(t, x, x->left);
			}
			else {
				TreeNode *y = TreeMininum(x->right);
				if (y->p == x) {
					//y是x的孩子节点
					z = y;
				}
				else {
					z = y->p;
					TreeTransplant(t, y, y->right);
					y->right = x->right;
					x->right->p = y;
				}
				TreeTransplant(t, x, y);
				y->left = x->left;
				x->left->p = y;
			}
			Balance(t,z);
			free(x);
			break;
		}
	}
}

void printNode(TreeNode *n) {
	if (n != NULL) {
		printf("[key=%d,value=%d,hight=%d]\n", n->key, n->val, n->hight);
	}
}

void printInOrder(AVLTree t) {
	if (t != NULL) {
		printInOrder(t->left);
		printNode(t);
		printInOrder(t->right);
	}
}

void printPreOrder(AVLTree t) {
	if (t != NULL) {
		printNode(t);
		printPreOrder(t->left);
		printPreOrder(t->right);
	}
}

void FreeMemory(AVLTree t) {
	if (t != NULL) {
		FreeMemory(t->left);
		FreeMemory(t->right);
		free(t);
	}
}


int main()
{
	AVLTree t = NULL;
	int a[10] = {1,9,2,8,3,7,4,5,6};
	for (int i:a) {
		AVLInsert(&t, i, i);
	}
	printPreOrder(t);
	printf("\n");
	TreeDelete(&t, 0);
	TreeDelete(&t, 1);
	printPreOrder(t);
	FreeMemory(t);
	_CrtCheckMemory();
	system("pause");
	return 0;
}
