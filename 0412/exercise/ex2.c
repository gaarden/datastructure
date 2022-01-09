#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct node* treePointer;
typedef struct node
{
	int data;
	treePointer leftChild, rightChild;
};

treePointer first;

treePointer read_data(char infile[]);
void search(treePointer ptr, int n);
void inorder(treePointer ptr);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	first = read_data(argv[1]);
	inorder(first);

	free(first);

	return EXIT_SUCCESS;
}

treePointer read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	treePointer root;

	MALLOC(root, sizeof(*root));
	root->leftChild = NULL;
	root->rightChild = NULL;

	int num = 0; // 입력받는 숫자

	fscanf(fp, "%d ", &num);
	root->data = num;

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &num);
		search(root, num);
	}

	fclose(fp);

	return root;
}

void search(treePointer ptr, int n)
{
	if (ptr->data >= n)
	{
		if (ptr->leftChild == NULL)
		{
			treePointer new;
			MALLOC(new, sizeof(*new));

			new->data = n;
			new->leftChild = NULL;
			new->rightChild = NULL;

			ptr->leftChild = new;
		}

		else
			search(ptr->leftChild, n);
	}

	else
	{
		if (ptr->rightChild == NULL)
		{
			treePointer new;
			MALLOC(new, sizeof(*new));

			new->data = n;
			new->leftChild = NULL;
			new->rightChild = NULL;

			ptr->rightChild = new;
		}

		else
			search(ptr->rightChild, n);
	}
}

void inorder(treePointer ptr)
{
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%d ", ptr->data);
		inorder(ptr->rightChild);
	}
}