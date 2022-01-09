// 0510 1¹ø

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 101
#define TRUE 1
#define FALSE 0
#define INT_MAX 10000

int size;
int start, finish;
int costMatrix[MAX_VERTICES][MAX_VERTICES];
int distanceCost[MAX_VERTICES];
short int check[MAX_VERTICES];
int row, col, weight;
int pathSave[MAX_VERTICES];
int pathPrint[MAX_VERTICES];
int top = -1;
int cnt;

void read_data(char infile[]);
void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[]);
int choose(int distance[], int n, short int found[]);
void push(int item);
int pop();

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);

	for (int i = 0; i <= size; i++)
	{
		for (int j = 0; j <= size; j++)
		{
			if ((i != j) && costMatrix[i][j] == 0)
				costMatrix[i][j] = INT_MAX;
		}
	}

	shortestPath(start, costMatrix, distanceCost, size, check);

	printf("%d ", start);

	for (int i = finish; (i != start) && (i != 0); i = pathSave[i])
	{
		if (pathSave[i] != 0)
			push(pathSave[i]);

		else
			break;
	}

	while (1)
	{
		printf("%d ", pop());
	}

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &size);
	fscanf(fp, "%d %d %d ", &row, &col, &weight);

	while (!feof(fp))
	{
		costMatrix[row][col] = weight;

		fscanf(fp, "%d %d %d ", &row, &col, &weight);
	}

	start = row;
	finish = col;

	fclose(fp);
}

void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[])
{
	int i, u, w;

	for (i = 0; i < n;i++)
	{
		found[i] = FALSE;

		if (cost[v][i] == 0 && v != i)
			distance[i] = INT_MAX;

		else
			distance[i] = cost[v][i];
	}

	found[v] = TRUE;
	distance[v] = 0;

	for (i = 0; i < n - 2; i++)
	{
		u = choose(distance, n, found);

		found[u] = TRUE;

		for (w = 1; w <= n; w++)
			if (found[w] == 0)
			{
				if (distance[u] + cost[u][w] < distance[w])
				{
					distance[w] = distance[u] + cost[u][w];
					pathSave[w] = u;
				}
			}
	}
}

int choose(int distance[], int n, short int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 1; i <= n; i++)
	{
		if (distance[i] < min && !found[i])
		{
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void push(int item)
{
	pathPrint[++top] = item;
}

int pop()
{
	if (top == -1)
	{
		printf("%d ", finish);
		exit(EXIT_FAILURE);
	}
	return pathPrint[top--];
}