#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10

typedef struct stack {
	int data[MAX_SIZE];
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

void push(stack *s, int val) {
	if (s->top >= MAX_SIZE) {
		fprintf(stderr, "stack overflow!!!");
	}
	else {
		s->top ++;
		s->data[s->top] = val;
	}
}

int pop(stack *s) {
	if (s->top == -1) {
		fprintf(stderr, "stack underflow!!!\n");
		return - 1;
	}
	else {
		int top = s->data[s->top];
		s->top--;
		return top;
	}
}

int main() {
	stack s;
	printf("栈是否为空？%d\n",isEmpty(&s));
	push(&s,1);
	push(&s, 2);
	push(&s, 3);
	int item;
	while (!isEmpty(&s)) {
		item = pop(&s);
		printf("%d\t", item);
	}
	printf("\n");
	return 0;
}
