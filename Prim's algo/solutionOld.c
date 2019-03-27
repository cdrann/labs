#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include<stdbool.h>
#include <stdlib.h>

typedef struct triple {
	int beg;
	int end;
	int len;

	struct triple *next;
} triple;

triple *createTriple(triple *arr, int j, int beg, int end, int len) {
	arr[j].beg = beg;
	arr[j].end = end;
	arr[j].len = len;
}

void addNode(triple *arr, triple *node) {
	while (arr->next)
		arr = arr->next;
	arr->next = node;
}

void BadInput(int num_vertices, int num_edges, FILE *fout) {
	assert(num_vertices != 1);
	if (num_vertices < 0 || num_vertices > 5000) {
		fputs("bad number of vertices", fout);
		exit(0);
	}
	if (num_edges < 0 || num_edges >(num_vertices * (num_vertices - 1)) / 2) {
		fputs("bad number of edges", fout);
		exit(0);
	}
	if (num_vertices == 0) {
		fputs("no spanning tree", fout);
		exit(0);
	}
}

void BadInputEdge(int num_vertices, int head, int tail, long long length, FILE *fout) {
	if (head < 1 || head > num_vertices || tail < 1 || tail > num_vertices) {
		fputs("bad vertex", fout);
		exit(0);
	}
	if (length < 0 || length > INT_MAX) {
		fputs("bad length", fout);
		exit(0);
	}
}

void BadNumLines(FILE *fout) {
	fputs("bad number of lines", fout);
	exit(0);
}

int minKey(long long *key, bool *mstSet, int num_vertices) {
	long long min = LONG_MAX;
	int min_index;

	for (int v = 0; v < num_vertices; v++) {
		if (mstSet[v] == false && key[v] < min) {
			min = key[v];
			min_index = v;
		}
	}

	return min_index;
}

int Comparator(triple *a, triple *b) {
	if (a->beg < b->beg) return -1;
	if (a->beg > b->beg) return 1;
	return 0;
}

int ComparatorLen(triple *a, triple *b) {
	if (a->len < b->len) return -1;
	if (a->len > b->len) return 1;
	return 0;
}

void print_pair(triple *res, int num_vertices, FILE *fout) {
	for (int i = 1; i < num_vertices; i++)
		fprintf(fout, "%d %d\n", res[i].beg, res[i].end);

}

int printMST(long long **graph, int *parent, int num_vertices, FILE *fout) {
	triple *arr = (triple *)malloc(sizeof(triple) * num_vertices);
	int j = 0;
	for (int i = 1; i < num_vertices; i++) {
		createTriple(arr, j, parent[i] + 1, arr[j].end = i + 1, graph[i][parent[i]]);
		j++;
	}
	qsort(arr, j + 1, sizeof(triple), (int(*)(const void*, const void*)) ComparatorLen); // по длине
	qsort(arr, j + 1, sizeof(triple), (int(*)(const void*, const void*)) Comparator); //по певрой вершине
	print_pair(arr, num_vertices, fout);
}

void primMST(long long **graph, int num_vertices, FILE *fout) {
	int *parent = (int *)malloc(num_vertices * sizeof(int));
	long long *key = (long long *)malloc(num_vertices * sizeof(long long));
	bool *mstSet = (bool *)malloc(num_vertices * sizeof(bool));

	for (int i = 0; i < num_vertices; i++) {
		key[i] = LONG_MAX;
		mstSet[i] = false;
	}

	key[0] = 0;
	parent[0] = -1;

	for (int count = 0; count < num_vertices - 1; count++) {
		int u = minKey(key, mstSet, num_vertices);

		mstSet[u] = true;

		for (int v = 0; v < num_vertices; v++) {
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
				parent[v] = u;
				key[v] = graph[u][v];
			}
		}
	}

	printMST(graph, parent, num_vertices, fout);
}

void isConnected(long long **graph, int num_vertices, FILE *fout) {
	long long sum = 0;

	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			sum += graph[i][j];
		}
		if (sum == 0) {
			fputs("no spanning tree", fout);
			exit(0);
		}
		sum = 0;
	}
}

int main() {
	FILE *fin = fopen("in.txt", "r");
	FILE *fout = fopen("out.txt", "w");

	if (fin == NULL) {
		fputs("bad input", fout);
		return 0;
	}

	unsigned int num_vertices;
	unsigned int num_edges;
	fscanf(fin, "%d", &num_vertices);
	fscanf(fin, "%d", &num_edges);
	BadInput(num_vertices, num_edges, fout);

	long long **graph = (long long **)malloc(num_vertices * sizeof(long long*));
	for (int i = 0; i < num_vertices; i++) {
		graph[i] = (long long*)malloc(num_vertices * sizeof(long long));
	}

	for (int i = 0; i < num_vertices; i++)
		for (int j = 0; j < num_vertices; j++)
			graph[i][j] = 0;

	int beg, end;
	long long len;
	for (int i = 0; i < num_edges; i++) {
		if (fscanf(fin, "%d", &beg) == EOF
			|| fscanf(fin, "%d", &end) == EOF || fscanf(fin, "%lld", &len) == EOF) {
			BadNumLines(fout);
		}
		BadInputEdge(num_vertices, beg, end, len, fout);
		beg--;
		end--;

		graph[beg][end] = len;
		graph[end][beg] = len;
	}
	isConnected(graph, num_vertices, fout);


	primMST(graph, num_vertices, fout);

	return 0;
}
