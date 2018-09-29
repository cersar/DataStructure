#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10

typedef struct TreeNode {
	int val;
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
		while(t != NULL) {
			push(&s, t);
			t = t->left;
		}
		t = pop(&s);
		printf("%d\t", t->val);
		t = t->right;
	}
}

int main() {
	stack s;
	Tree t;
	TreeNode n1 = { 1 };
	TreeNode n2 = { 2 };
	TreeNode n3 = { 3 };
	TreeNode n4 = { 4 };
	TreeNode n5 = { 5 };
	t = &n3;
	t->left = &n1;
	n1.right = &n2;
	t->right = &n5;
	n5.left = &n4;
	TrivalByStack(t);
	return 0;
}
