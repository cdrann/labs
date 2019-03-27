#ifndef H_TRIPLE
#define H_TRIPLE
    
typedef struct triple {
	int beg;
	int end;
	int len;
} triple;

triple *TripleConstructor(triple *tr, int j, int beg, int end, int len) {
	tr[j].beg = beg;
	tr[j].end = end;
	tr[j].len = len;
}

void PrintTriple(triple *res, int num_vertices, FILE *fout) {
	for (int i = 1; i < num_vertices; i++)
		fprintf(fout, "%d %d\n", res[i].beg, res[i].end);
}

#endif
