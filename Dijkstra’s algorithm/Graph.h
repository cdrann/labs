#pragma once
#include "List.h"
#include "ListTuple.h"

typedef struct graphNode {
	listTuple *neighbours;
	list *parents;
} graphNode;

