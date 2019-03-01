#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct list {
	int number;

	struct list *next;
} list;

list *initList(int i);

list *createNode(int node);

void addNode(list *AdjList, list *node);

//void removeEdge(int target, list *AdjList);