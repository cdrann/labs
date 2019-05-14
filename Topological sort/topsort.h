#pragma once

#ifndef H_TOPSORT
#define H_TOPSORT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

void DFS(short current, struct Stack *stack, short **matrix, short *color, short *count, FILE *fout);

void top_sort(Stack *stack, short **matrix, short *color, short *count, short num_vertices, FILE *fout);

#endif