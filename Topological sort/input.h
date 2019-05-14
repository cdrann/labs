#pragma once

#ifndef H_INPUT
#define H_INPUT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void BadInputGraph(short num_vertices, int num_edges, FILE *fout);

void BadInputEdge(int head, int tail, short num_vertices, FILE *fout);

void BadNumLines(int num_strings, int num_edges, short num_vertices, FILE *fout);

#endif