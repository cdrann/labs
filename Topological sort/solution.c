#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "input.h"
#include "stack.h"
#include "topsort.h"

int main() {
	FILE *fin = fopen("in.txt", "r");
	if (fin == NULL) {
		puts("error openning file");
		system("pause");
		exit(0);
	}
	FILE *fout = fopen("out.txt", "w");

	short num_vertices;
	int num_edges;
	scanf("%hd", &num_vertices);
	scanf("%d", &num_edges);
	assert(num_edges != -1 || num_vertices != -1);
	
	short *count = NULL;
	count = (short *)calloc((num_vertices + 1), sizeof(short));

	short **matrix = NULL;
	matrix = (short **)calloc((num_vertices + 1), sizeof(short *));

	int num_strings = 0;
	int beg = 0, end = 0;
	for (int i = 0; i < num_edges; i++) {
		scanf("%d", &beg);
		scanf("%d", &end);
		if (beg == 0 && end == 0) {
			break;
		}
		else {
			BadInputEdge(beg, end, num_vertices, fout);
			count[beg]++;
			matrix[beg] = (short *)realloc(matrix[beg], sizeof(short) * (count[beg] + 1));
			matrix[beg][count[beg]] = end;
			num_strings++;
		}
	}
	BadNumLines(num_strings, num_edges, num_vertices, fout);
	BadInputGraph(num_vertices, num_edges, fout);

	short *color = NULL;
	color = (short *)calloc((num_vertices + 1), sizeof(short));
	Stack *stack = StackConstructor();
	top_sort(stack, matrix, color, count, num_vertices, fout);
	PrintStack(stack, fout);
	StackDestructor(stack);

	free(matrix);
	free(color);
	free(count);

	fclose(fin);
	fclose(fout);
	return 0;
}