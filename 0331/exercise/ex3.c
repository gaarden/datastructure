#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct listNode* listPointer;
typedef struct listNode
{
	int data;
	listPointer link;
};
listPointer first = NULL;
listPointer second = NULL;
listPointer x = NULL;
listPointer trail = NULL;

#define MALLOC(p,s)\
if (!((p) = malloc(s)))\
{\
	fprintf(stderr, "insufficient memory");\
	exit(EXIT_FAILURE);\
}

void read_data(char infile[]);
void findInsert(listPointer first, listPointer* x, int data);
void insert(listPointer* first, listPointer x, int value);
void findDelete(listPointer first, listPointer* trail, listPointer* x, int data);
void delete(listPointer* first, listPointer trail, listPointer x);
void addlist();
void printList(listPointer first);


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	addlist();
	printList(first);

	return 0;
}

void read_data(char infile[])
{
	int what;

	FILE* fp;
	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	do
	{
		fscanf(fp, "%d ", &what);

		listPointer temp;
		listPointer back = NULL;

		temp = first;

		if (what == -1)
			break;
		/*
		findInsert(first, &x, what);
		insert(&first, x, what);
		*/
		
		while (temp != NULL)
		{
			if (temp->data > what)
			{
				insert(&first, back, what);
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
			insert(&first, back, what);
		

	} while (what != -1);

	do
	{
		fscanf(fp, "%d ", &what);

		listPointer temp;
		listPointer back = NULL;

		temp = second;

		if (what == -1)
			break;
		/*
		findInsert(second, &x, what);
		insert(&second, x, what);
		*/
		
		
		while (temp != NULL)
		{
			if (temp->data > what)
			{
				insert(&second, back, what);
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
			insert(&second, back, what);
		

	} while (what != -1);


	fclose(fp);
}

void findInsert(listPointer first, listPointer* x, int data)
{
	listPointer pre = NULL;

	if (first == NULL)
	{
		*x = first;
	}

	else
	{
		for (; first; first = first->link)
		{
			if (first->data > data)
			{
				*x = pre;
				break;
			}
			else
				pre = first;

			*x = pre;
		}
	}
}

void insert(listPointer* first, listPointer x, int value)
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

void findDelete(listPointer first, listPointer* trail, listPointer* x, int data)
{
	listPointer curr = NULL;

	for (; first; first = first->link)
	{
		if (first->data == data)
		{
			*trail = curr;
			*x = first;
			break;
		}
		curr = first;
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

void addlist()
{
	for (; second;)
	{
		listPointer temp;
		listPointer back = NULL;

		temp = first;
		
		if (temp->data > second->data)
		{
			insert(&first, back, second->data);
			break;
		}

		else if (temp->data < second->data)
		{
				back = temp;
				temp = temp->link;
		}
		else
		{
			printf("FAILURE ");
			break;
		}

		if (temp == NULL)
			insert(&first, back, second->data);

		insert(&first, x, second->data);
		findDelete(second, &trail, &x, second->data);
		delete(&second, trail, x);
	}
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