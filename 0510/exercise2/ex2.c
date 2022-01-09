#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 101
#define TRUE 1
#define FALSE 0

typedef struct
{
    int select;
    int change;
} element;

int size;
int start = 1;
int finish;
int costMatrix[MAX_VERTICES][MAX_VERTICES];
int distanceCost[MAX_VERTICES];
short int check[MAX_VERTICES];
int row, col;
int pathSave[MAX_VERTICES];
int pathPrint[MAX_VERTICES];
element path[MAX_VERTICES];
int top = -1;
int k;

void read_data(char infile[]);
void longestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[]);
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

	longestPath(start, costMatrix, distanceCost, size, check);

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

	while (!feof(fp))
	{
		fscanf(fp, "%d %d ", &row, &col);
		costMatrix[row][col] = 1;
	}

	fclose(fp);
}

void longestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[])
{
    int u, cnt = 0;

    for (int i = 1; i <= n; i++)
    {
        found[i] = FALSE;
        distance[i] = cost[v][i];

        if (distance[i] > 0)
        {
            path[k].select = v;
            path[k++].change = i;
        }
    }
    found[v] = TRUE;
    distance[v] = 0;

    for (int i = 1; i <= n - 2; i++)
    {
        u = choose(distance, n, found);
        found[u] = TRUE;

        for (int w = 1; w <= n; w++)
        {
            if (cost[w][u])
            {
                if (distance[u] < cost[w][u] + distance[w])
                {
                    distance[u] = cost[w][u] + distance[w];
                    path[k].select = w;
                    path[k++].change = u;
                }
            }
        }

        for (int w = 2; w <= n; w++) //distance[1(start)]값은 변동 안되게
        {
            if (cost[u][w])
            {
                distance[w] = distance[u] + cost[u][w];
                path[k].select = u;
                path[k++].change = w;
            }
        }
    }

    //1(start)로 끝나는 edge가 있는 경우
    for (int i = 1; i <= n; i++)
    {
        if (cost[i][start])
        {
            if (distance[start] < cost[i][start] + distance[i])
            {
                distance[start] = cost[i][start] + distance[i];
                path[k].select = i;
                path[k++].change = start;
            }
        }
    }

    //가장 큰 distance찾기
    for (int i = 1; i <= n; i++)
    {
        if (cnt < distance[i])
        {
            cnt = distance[i];
            finish = i;
        }
    }

}

int choose(int distance[], int n, short int found[])
{
	int i, max, maxpos;
	max = 0;
	maxpos = -1;
	for (i = 1; i <= n; i++)
	{
		if (distance[i] < max && !found[i])
		{
			max = distance[i];
			maxpos = i;
		}
	}
	return maxpos;
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