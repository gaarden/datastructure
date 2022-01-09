// 0503 1¹ø

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
if (!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct
{
	int key;
}element;

typedef struct node* treePointer;
typedef struct node
{
	element data;
	treePointer leftChild, rightChild;
};

void read_data(char infile[]);
void insert(treePointer* node, int k);
void delete(treePointer* ptr, int k);
element* modifiedSearch(treePointer root, int k);
void printBST(treePointer node);
void freeBST(treePointer node);

treePointer bin;
int start, finish;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	freeBST(bin);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int k = 0;

	fscanf(fp, "%d ", &k);
	MALLOC(bin, sizeof(treePointer));
	bin->leftChild = NULL;
	bin->rightChild = NULL;
	bin->data.key = k;

	while (1)
	{
		fscanf(fp, "%d ", &k);

		if (k == -1)
			break;

		else
			insert(&bin, k);
	}



	while (!feof(fp))
	{
		fscanf(fp, "%d %d ", &start, &finish);

		printBST(bin);
	}

	fclose(fp);
}