#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

void BadInput(int num_vertices, int num_edges, FILE *fout) {
	assert(num_vertices != 1);
	if (num_vertices < 0 || num_vertices > 5000) {
		fputs("bad number of vertices", fout);
		exit(0);
	}
	if (num_edges < 0 || num_edges >(num_vertices * (num_vertices - 1)) / 2) {
		fputs("bad number of edges", fout);
		exit(0);
	}
}

void BadInputEdge(int num_vertices, int head, int tail, long long length, FILE *fout) {
	if (head < 1 || head > num_vertices || tail < 1 || tail > num_vertices) {
		fputs("bad vertex", fout);
		exit(0);
	}
	if (length < 0 || length > INT_MAX) {
		fputs("bad length", fout);
		exit(0);
	}
}

void BadNumLines(FILE *fout) {
	fputs("bad number of lines", fout);
	exit(0);
}

typedef struct MST {
	int beg;
	int end;
	struct MST *next;
} MST;

void push_back(MST *head, int beg, int end) {
	MST *cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = (MST *)malloc(sizeof(MST));
	assert(cur->next != NULL);
	cur->next->beg = beg;
	cur->next->end = end;
	cur->next->next = NULL;
}

void freeMST(MST **head) {
   MST *cur = *head; 
   MST *next; 
  
   while (cur != NULL)  { 
       next = cur->next; 
       free(cur); 
       cur = next; 
   } 
    
   *head = NULL; 
}


void printMST(MST *head, FILE *output_file) {
	MST *edge = head;
	while (edge->next != NULL) {
		edge = edge->next;
		fprintf(output_file, "%d %d\n", edge->beg, edge->end);
	}
}

typedef struct TDSU {
	struct TDSU *parent;
} TDSU;

TDSU *MakeSets(int num_vertices) {
	TDSU *sets = (TDSU*)malloc(num_vertices * sizeof(TDSU));
	assert(sets != NULL);

	int num_sets = num_vertices;
	for (int i = 0; i < num_sets; i++)
		sets[i].parent = &sets[i];
	return sets;
}

TDSU *FindSet(TDSU *s) {
	if (s == s->parent)
		return s;
	else {
		TDSU *parent = FindSet(s->parent);
		s->parent = parent;
		return parent;
	}
}

TDSU *MergeSets(TDSU *a, TDSU *b) {
	a->parent = b;
	return a;
}

typedef struct {
	int beg;
	int end;
	double len;
} triple;

int Comparator(triple *a, triple *b) {
	if (a->len > b->len) return 1;
	if (a->len < b->len) return -1;
	return 0;
}

void MakeGraph(int edgeID, MST *head, triple *edge) {
	edge[edgeID].beg++;
	edge[edgeID].end++;
	push_back(head, edge[edgeID].beg, edge[edgeID].end);
}

void KruskalMST(int num_vertices, int num_edges, triple *edges, FILE *fout) {
	TDSU *sets = MakeSets(num_vertices);
	int num_sets = num_vertices;

	MST *MinimumSpanningTree = (MST *)malloc(sizeof(MST));
	assert(MinimumSpanningTree != NULL);
	MinimumSpanningTree->next = NULL;

	for (int i = 0; num_sets > 1 && i < num_edges; i++) { // => while!! -> (!= && > && <) 
		if (FindSet(&sets[edges[i].beg]) == FindSet(&sets[edges[i].end]))
			continue;

		MergeSets(FindSet(&sets[edges[i].beg]), FindSet(&sets[edges[i].end]));
		num_sets--;
		MakeGraph(i, MinimumSpanningTree, edges);
	}

	if (num_sets != 1)
		fprintf(fout, "no spanning tree");
	else
		printMST(MinimumSpanningTree, fout);

	freeMST(&MinimumSpanningTree);
}

int main() {
	FILE *inputfile = fopen("in.txt", "r");
	assert(inputfile != NULL);
	FILE *outputfile = fopen("out.txt", "w");

	unsigned int num_vertices;
	unsigned int num_edges;
	fscanf(inputfile, "%d", &num_vertices);
	fscanf(inputfile, "%d", &num_edges);
	BadInput(num_vertices, num_edges, outputfile);

	triple *edges = (triple*)malloc(num_edges * sizeof(triple));
	assert(edges != NULL);
	for (int i = 0; i < num_edges; i++) {
		if (fscanf(inputfile, "%d", &edges[i].beg) == EOF
			|| fscanf(inputfile, "%d", &edges[i].end) == EOF || fscanf(inputfile, "%lf", &edges[i].len) == EOF) {
			BadNumLines(outputfile);
		}
		BadInputEdge(num_vertices, edges[i].beg, edges[i].end, edges[i].len, outputfile);
		edges[i].beg--;
		edges[i].end--;
	}
	qsort(edges, num_edges, sizeof(triple), (int(*)(const void*, const void*)) Comparator);

	KruskalMST(num_vertices, num_edges, edges, outputfile);

    free(edges);
	fclose(inputfile);
	fclose(outputfile);
	return 0;
}
