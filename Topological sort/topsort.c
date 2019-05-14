#pragma once

#include "topsort.h"

void DFS(short current, struct Stack *stack, short **matrix, short *color, short *count, FILE *fout) {
	color[current] = 1;
	for (int i = 1; i <= count[current]; i++) {
		if (color[matrix[current][i]] == 0)
			DFS(matrix[current][i], stack, matrix, color, count, fout);
		if (color[matrix[current][i]] == 1) {
			fputs("impossible to sort", fout);
			exit(0);
		}
	}
	color[current] = 2;
	Push(stack, current);
}

void top_sort(Stack *stack, short **matrix, short *color, short *count, short num_vertices, FILE *fout) {
	for (int i = 1; i <= num_vertices; i++) 
		if (color[i] == 0) 
			DFS(i, stack, matrix, color, count, fout);
}
