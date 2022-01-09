#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct listNode* listPointer;
typedef struct listNode
{
	int data;
	listPointer link;
};
listPointer front = NULL;

#define MALLOC(p,s)\
if (!((p) = malloc(s)))\
{\
	fprintf(stderr, "insufficient memory");\
	exit(EXIT_FAILURE);\
}

void read_data(char infile[]);
void insert(listPointer* first, listPointer x, int value);
void delete(listPointer* first, listPointer trail, listPointer x);
void printList(listPointer first);


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printList(front);

	return 0;
}

void read_data(char infile[])
{
	char how;
	int what;

	FILE* fp;
	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%c %d ", &how, &what);
		listPointer temp;
		listPointer back = NULL;
		
		temp= front;

		if (how == 'i')
		{
			while (temp != NULL)
			{
				if (temp->data > what)
				{
					insert(&front, back, what);
					break;
				}

				else if (temp->data < what)
				{
					back = temp;
					temp = temp->link;
				}
				else
				{
					printf("FAILURE ");
					break;
				}
				
			}

			if (temp == NULL)
				insert(&front, back, what);
		}

		else
		{
			while (temp != NULL)
			{
				if (temp->data > what)
				{
					printf("FAILURE ");
					break;
				}

				else if (temp->data < what)
				{
					back = temp;
					temp = temp->link;
				}
				else
				{
					delete(&front, back, temp);
					break;
				}
			}

			if (temp == NULL)
				printf("FAILURE ");
		}
	}

	fclose(fp);
}

void insert(listPointer *first, listPointer x, int value)
{
	listPointer temp1;
	MALLOC(temp1, sizeof(*temp1));
	temp1->data = value;
	temp1->link = NULL;

	if (*first)
	{
		if (x != NULL)
		{
			temp1->link = x->link;
			x->link = temp1;
		}

		else
		{
			temp1->link = *first;
			*first = temp1;
		}
	}

	else
	{
		temp1->link = NULL;
		*first = temp1;
	}

}

void delete(listPointer* first, listPointer trail, listPointer x)
{
	if (trail)
		trail->link = x->link;

	else
		*first = (*first)->link;
	free(x);
}

void printList(listPointer first)
{
	listPointer temp2;
	for (;first;)
	{
		printf("%d ", first->data);
		temp2 = first;
		first = temp2->link;
		free(temp2);
	}
}