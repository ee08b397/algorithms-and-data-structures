#include <stdlib.h>
#include <stdio.h>

//#define NODES 6
#define NODES 10
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define INFINITE 10000000

void push(const int **C, int **F, int *excess, int u, int v) {
	int send = MIN(excess[u], C[u][v] - F[u][v]);
	F[u][v] += send;
	F[v][u] -= send;
	excess[u] -= send;
	excess[v] += send;
}

void relabel(const int **C, const int **F, int *height, int u) {
	int v;
	int min_height = INFINITE;
	for (v = 0; v < NODES; ++v) {
		if (C[u][v] - F[u][v] > 0) {
			min_height = MIN(min_height, height[v]);
			height[u] = min_height + 1;
		}
	}
}

void discharge(const int **C, int **F, int *excess, int *height, int *seen, int u) {
	while (excess[u] > 0) {
		if (seen[u] < NODES) {
			int v = seen[u];
			if ((C[u][v] - F[u][v] > 0) && (height[u] > height[v])){
				push(C, F, excess, u, v);
			}
			else
				seen[u] += 1;
		} else {
			relabel(C, (const int**)F, height, u);
			seen[u] = 0;
		}
	}
}

void moveToFront(int i, int *A) {
	int temp = A[i];
	int n;
	for (n = i; n > 0; --n){
		A[n] = A[n-1];
	}
	A[0] = temp;
}

int pushRelabel(const int **C, int **F, int source, int sink) {
	int *excess, *height, *list, *seen, i, p;

	excess = (int *) calloc(NODES, sizeof(int));
	height = (int *) calloc(NODES, sizeof(int));
	seen = (int *) calloc(NODES, sizeof(int));

	list = (int *) calloc((NODES-2), sizeof(int));

	for (i = 0, p = 0; i < NODES; ++i){
		if((i != source) && (i != sink)) {
			list[p] = i;
			++p;
		}
	}

	height[source] = NODES;
	excess[source] = INFINITE;
	for (i = 0; i < NODES; ++i)
		push(C, F, excess, source, i);

	p = 0;
	while (p < NODES - 2) {
		int u = list[p];
		int old_height = height[u];
		discharge(C, F, excess, height, seen, u);
		if (height[u] > old_height) {
			moveToFront(p,list);
			p=0;
		}
		else
			p += 1;
	}
	int maxflow = 0;
	for (i = 0; i < NODES; ++i)
		maxflow += F[source][i];

	free(list);

	free(seen);
	free(height);
	free(excess);

	return maxflow;
}

void printMatrix(const int **M) {
	int i,j;
	for (i = 0; i < NODES; ++i) {
		for (j = 0; j < NODES; ++j)
			printf("%d\t",M[i][j]);
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	int **flow, **capacities, i;
	flow = (int **) calloc(NODES, sizeof(int*));
	capacities = (int **) calloc(NODES, sizeof(int*));
	for (i = 0; i < NODES; ++i) {
		flow[i] = (int *) calloc(NODES, sizeof(int));
		capacities[i] = (int *) calloc(NODES, sizeof(int));
	}

	//Sample graph
	/*
	capacities[0][1] = 2;
	capacities[0][2] = 9;
	capacities[1][2] = 1;
	capacities[1][3] = 0;
	capacities[1][4] = 0;
	capacities[2][4] = 7;
	capacities[3][5] = 7;
	capacities[4][5] = 4;
	*/

	/*
	for (i = 1; i <= 10; ++i) {
		capacities[0][i + 10] = 1;
		capacities[i][21] = 1;
	}
	capacities[11][1] = 1;
	capacities[11][3] = 1;
	capacities[11][4] = 1;
	capacities[12][1] = 1;
	capacities[12][2] = 1;
	capacities[12][8] = 1;
	capacities[13][1] = 1;
	capacities[13][3] = 1;
	capacities[14][3] = 1;
	capacities[14][4] = 1;
	capacities[15][3] = 1;
	capacities[15][4] = 1;
	capacities[16][2] = 1;
	capacities[16][5] = 1;
	capacities[16][7] = 1;
	capacities[17][5] = 1;
	capacities[17][6] = 1;
	capacities[17][10] = 1;
	capacities[18][5] = 1;
	capacities[18][6] = 1;
	capacities[18][7] = 1;
	capacities[18][8] = 1;
	capacities[18][10] = 1;
	capacities[19][9] = 1;
	capacities[20][4] = 1;
	capacities[20][9] = 1;
	*/

	capacities[0][1] = 12;
	capacities[0][2] = 1;
	capacities[0][3] = 2;
	capacities[1][2] = 1;
	capacities[1][4] = 7;
	capacities[1][5] = 5;
	capacities[2][5] = 1;
	capacities[2][6] = 7;
	capacities[3][2] = 3;
	capacities[3][5] = 2;
	capacities[3][6] = 5;
	capacities[4][2] = 2;
	capacities[4][5] = 3;
	capacities[4][7] = 3;
	capacities[5][6] = 2;
	capacities[5][7] = 3;
	capacities[5][8] = 1;
	capacities[6][8] = 9;
	capacities[7][8] = 1;
	capacities[7][9] = 4;
	capacities[8][9] = 11;

	
	printf("Capacity:\n");
	printMatrix((const int**)capacities);

	printf("Max Flow:\n%d\n", pushRelabel((const int**)capacities, flow, 0, NODES - 1));

	printf("Flows:\n");
	printMatrix((const int**)flow);

	for (i = 0; i < NODES; ++i) {
		free(flow[i]);
		free(capacities[i]);
	}
	free(flow);
	free(capacities);
	return 0;
}
