#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct listTuple {
	int nextNode;
	int lenPath;

	struct listTuple *next;
} listTuple;


listTuple *initListTuple(int i);

listTuple *createNodeTuple(int node, int len);

void addNodeTuple(listTuple *AdjList, listTuple *node);
