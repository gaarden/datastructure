/*
• Task: postfix expression 을 Binary tree 로 관리하는 프로그램을 작성하라
• Input:
– postfix expression
• 예: abc+/def-/*
• Output:
– binary tree 의 내용을 inorder 로 출력
– 예: (a/(b+c))*(d/(e-f))
• Specification
– Binary tree 의 표현은 linked representation 을 사용할 것
– 파일로 부터 postfix expression 입력
– Binary tree 의 노드는 (leftchildlink, data, value, rightchildlink) 로 구성할 것
• Value 는 각 문자의 값을 저장할 공간 (3번 문제에서 쓰임) 으로 float 형
– Binary tree 생성 과정에서 stack 필요 (생성된 노드의 pointer 저장)
– Binary tree 의 생성이 끝나면 inorder 로 data 부분을 출력
• 각 subtree 의 시작과 끝에 ‘(‘ 과 ‘)’ 를 출력
– 작업이 모두 끝나면 할당된 메모리공간 모두 해제
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct node* treePointer;
typedef struct node
{
	int data;
	float value;
	treePointer leftChildlink, rightChildlink;
};

typedef struct
{
	treePointer key;
} element;
element stack[MAX_SIZE];

treePointer expression;
treePointer node;
element tree1;
element tree2;

int check;
int top = -1;

treePointer read_data(char infile[]);
void push(element item);
element pop();
void inorder(treePointer ptr);
void freeTree(treePointer ptr);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	expression = read_data(argv[1]);
	inorder(expression);

	freeTree(expression);

	return EXIT_SUCCESS;
}

treePointer read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	element data;
	char member = '/0';

	while (!feof(fp))
	{
		MALLOC(node, sizeof(*node));
		node->leftChildlink = NULL;
		node->rightChildlink = NULL;

		fscanf(fp, "%c ", &member);

		if (member != '+' && member != '-' && member != '*' && member != '/') // 문자
		{
			node->data = member;
			data.key = node;

			push(data);
		}

		else // 연산 기호
		{
			tree1 = pop();
			tree2 = pop();

			node->data = member;
			node->rightChildlink = tree1.key;
			node->leftChildlink = tree2.key;

			data.key = node;

			push(data);
		}
	}
	
	fclose(fp);

	return node;
}

void push(element item)
{
	if (top >= MAX_SIZE - 1)
		;
	stack[++top] = item;
}

element pop()
{
	if (top == -1)
		;
	return stack[top--];
}

void inorder(treePointer ptr)
{
	if (ptr)
	{
		if (ptr->leftChildlink != NULL && ptr->rightChildlink != NULL)
			printf("(");

		inorder(ptr->leftChildlink);
		printf("%c", ptr->data);
		inorder(ptr->rightChildlink);

		if (ptr->leftChildlink != NULL && ptr->rightChildlink != NULL)
			printf(")");
	}

	check = 0;
}

void freeTree(treePointer ptr)
{
	if (ptr)
	{
		freeTree(ptr->leftChildlink);
		free(ptr);
		freeTree(ptr->rightChildlink);
	}
}