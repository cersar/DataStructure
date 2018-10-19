#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10

typedef struct TreeNode {
	int val;
	TreeNode *parent = NULL;
	TreeNode *left = NULL;
	TreeNode *right = NULL;
}*Tree;

typedef struct stack {
	TreeNode *data[MAX_SIZE];
	int top = -1;
}stack;

//注意c语言没有引用传递，只有值传递和指针传递（指针传递本质上也是值传递）
//结构体的传递方式为值传递
bool isEmpty(stack *s) {
	if (s->top == -1) {
		return true;
	}
	else {
		return false;
	}
}

void push(stack *s, TreeNode *n) {
	if (s->top >= MAX_SIZE) {
		fprintf(stderr, "stack overflow!!!");
	}
	else {
		s->top++;
		s->data[s->top] = n;
	}
}

TreeNode* pop(stack *s) {
	if (s->top == -1) {
		fprintf(stderr, "stack underflow!!!\n");
		return NULL;
	}
	else {
		TreeNode *top = s->data[s->top];
		s->top--;
		return top;
	}
}

//使用栈实现非递归的中序遍历
void TrivalByStack(Tree t) {
	stack s;
	while (t != NULL || !isEmpty(&s)) {
		while (t != NULL) {
			push(&s, t);
			t = t->left;
		}
		t = pop(&s);
		printf("%d\t", t->val);
		t = t->right;
	}
	printf("\n");
}

//递归的中序遍历
void TrivalInOrder(Tree t) {
	if (t != NULL) {
		printf("%d\t", t->val);
		TrivalInOrder(t->left);
		TrivalInOrder(t->right);
	}
}

//返回最小节点
TreeNode *TreeMin(Tree t) {
	while (t->left != NULL) {
		t = t->left;
	}
	return t;
}

//返回最大节点
TreeNode *TreeMax(Tree t) {
	while (t->right != NULL) {
		t = t->right;
	}
	return t;
}

//插入节点
void TreeInsert(Tree *t, TreeNode *n) {
	TreeNode *parent = NULL;
	TreeNode *p = *t;
	while (p != NULL) {
		parent = p;
		if (n->val<p->val) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	n->parent = parent;
	if (parent == NULL) {
		*t = n;
	}
	else if (n->val < parent->val) {
		parent->left = n;
	}
	else {
		parent->right = n;
	}
}

//返回后继
TreeNode *TreeSucessor(TreeNode *n) {
	if (n->right != NULL) {
		return TreeMin(n->right);
	}
	else {
		TreeNode *parent = n->parent;
		while (parent != NULL&&parent->left != n) {
			n = parent;
			parent = parent->parent;
		}
		return parent;
	}
}

//返回前驱
TreeNode *TreePredecessor(TreeNode *n) {
	if (n->left != NULL) {
		return TreeMax(n->left);
	}
	else {
		TreeNode *parent = n->parent;
		while (parent != NULL&&parent->right != n) {
			n = parent;
			parent = parent->parent;
		}
		return parent;
	}
}

//树的移栽（用另一棵子树替换一棵子树并成为其双亲的节点）
//适用情况：
//1）u仅有一个节点.
//2）v=u.left且v.right=NULL，此时需要在调用TransPlantTree之后需要更新v.right和u.right.parent.
//2）v=u.right且v.right=NULL，此时需要在调用TransPlantTree之后需要更新v.left和u.left.parent.
void TransPlantTree(Tree *t, TreeNode *u, TreeNode *v) {
	if (u->parent == NULL) {
		*t = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	if (v != NULL) {
		v->parent = u->parent;
	}
}

//删除节点
//三种情况
void TreeDelete(Tree *t, TreeNode *n) {
	if (n->left == NULL) {
		TransPlantTree(t, n, n->right);
	}
	else if (n->right == NULL) {
		TransPlantTree(t, n, n->right);
	}
	else {
		TreeNode *sucessor = TreeSucessor(n);
		if (sucessor->parent != n) {
			TransPlantTree(t, sucessor, sucessor->right);
			sucessor->right = n->right;
			n->right->parent = sucessor;
		}
		TransPlantTree(t, n, sucessor);
		sucessor->left = n->left;
		n->left->parent = sucessor;
	}
}

//寻找最大Node，Node.val<=key
TreeNode *floor(Tree t,int key) {
	if (t == NULL) {
		return NULL;
	}
	if (t->val>key) {
		return floor(t->left, key);
	}
	else {
		TreeNode *n = floor(t->right, key);
		if (n == NULL) {
			return t;
		}
		else {
			return n;
		}
	}
}

//寻找最小Node，Node.val>=key
TreeNode *ceil(Tree t, int key) {
	if (t == NULL) {
		return NULL;
	}
	if (t->val<key) {
		return ceil(t->right, key);
	}
	else {
		TreeNode *n = ceil(t->left, key);
		if (n == NULL) {
			return t;
		}
		else {
			return n;
		}
	}
}

int main() {
	stack s;
	Tree t = NULL;
	TreeNode n1 = { 1 };
	TreeNode n2 = { 2 };
	TreeNode n3 = { 3 };
	TreeNode n4 = { 4 };
	TreeNode n5 = { 5 };
	TreeNode n6 = { 6 };
	TreeInsert(&t, &n2);
	TreeInsert(&t, &n1);
	TreeInsert(&t, &n3);
	TreeInsert(&t, &n4);
	TreeInsert(&t, &n6);
	TreeInsert(&t, &n5);
	TreeDelete(&t, &n1);
	TreeDelete(&t, &n4);
	TrivalInOrder(t);
	printf("\n");
	printf("%d的后继为%d\n", n5.val, TreeSucessor(&n5)->val);
	printf("%d的前驱为%d\n", n5.val, TreePredecessor(&n5)->val);
	printf("树的最小节点%d\n", TreeMin(t)->val);
	printf("树的最大节点%d\n", TreeMax(t)->val);
	int key = 4;
	printf("小于等于%d的最大节点为%d\n", key, floor(t, key)->val);
	printf("大于等于%d的最小节点为%d\n", key, ceil(t, key)->val);
	return 0;
}
