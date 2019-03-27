#ifndef H_INPUT
#define H_INPUT

#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include<stdbool.h>
#include <stdlib.h>

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

void isConnected(long long **graph, int num_vertices, FILE *fout) {
	long long lenEdges = 0;

	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			lenEdges += graph[i][j];
		}
		if (lenEdges == 0) {
			fputs("no spanning tree", fout);
			exit(0);
		}
		lenEdges = 0;
	}
}

#endif