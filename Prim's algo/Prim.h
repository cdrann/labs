#ifndef H_PRIM
#define H_PRIM

int FindMinNotIncluded(long long *key, bool *includedToMST, int num_vertices) {
	long long min = LONG_MAX;
	int min_index;
	for (int i = 0; i < num_vertices; i++)
		if (includedToMST[i] == false && key[i] < min) {
			min = key[i];
			min_index = i;
		}

	return min_index;
}

int ComparatorBeg(triple *a, triple *b) {
	if (a->beg < b->beg) return -1;
	if (a->beg > b->beg) return 1;
	return 0;
}

int ComparatorLen(triple *a, triple *b) {
	if (a->len < b->len) return -1;
	if (a->len > b->len) return 1;
	return 0;
}

int printMST(long long **graph, int *MST, int num_vertices, FILE *fout) {
	triple *arrMST = (triple *)malloc(sizeof(triple) * num_vertices);
	int j = 0;
	for (int i = 1; i < num_vertices; i++) {
		TripleConstructor(arrMST, j, MST[i] + 1, arrMST[j].end = i + 1, graph[i][MST[i]]);
		j++;
	}

	qsort(arrMST, j + 1, sizeof(triple), (int(*)(const void*, const void*)) ComparatorLen);
	qsort(arrMST, j + 1, sizeof(triple), (int(*)(const void*, const void*)) ComparatorBeg);
	PrintTriple(arrMST, num_vertices, fout);
}

void PrimMST(long long **graph, int num_vertices, FILE *fout) {
	int *MST = (int *)malloc(num_vertices * sizeof(int));
	long long *minWeights = (long long *)malloc(num_vertices * sizeof(long long));
	bool *includedToMST = (bool *)malloc(num_vertices * sizeof(bool));

	for (int i = 1; i < num_vertices; i++) {
		minWeights[i] = LONG_MAX;
		includedToMST[i] = false;
	}
	minWeights[0] = 0;
	MST[0] = -1;
	includedToMST[0] = false;

	for (int i = 0; i < num_vertices - 1; i++) {
		int minVertex = FindMinNotIncluded(minWeights, includedToMST, num_vertices);
		includedToMST[minVertex] = true;

		for (int j = 0; j < num_vertices; j++)
			if (graph[minVertex][j] && includedToMST[j] == false && graph[minVertex][j] < minWeights[j]) {
				MST[j] = minVertex;
				minWeights[j] = graph[minVertex][j];
			}
	}

	printMST(graph, MST, num_vertices, fout);
}

#endif