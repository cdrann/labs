#pragma once

#include "input.h"

void BadInputGraph(short num_vertices, int num_edges, FILE *fout) {
	if (num_vertices > 1000 || num_vertices < 0) {
		fputs("bad number of vertices", fout);
		exit(0);
	}
	if (num_edges < 0 || num_edges >(num_vertices * (num_vertices - 1)) / 2) {
		fputs("bad number of edges", fout);
		exit(0);
	}
}

void BadInputEdge(int head, int tail, short num_vertices, FILE *fout) {
	if (head < 1 || head > num_vertices || tail < 1 || tail > num_vertices) {
		fputs("bad vertex", fout);
		exit(0);
	}
}

void BadNumLines(int num_strings, int num_edges, short num_vertices, FILE *fout) {
	if (num_vertices == 0) return;
	num_strings += 2;
	if (num_strings < num_edges + 2) {
		fputs("bad number of lines", fout);
		exit(0);
	}
}

