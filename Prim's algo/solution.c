#include "input.h"
#include "triple.h"
#include "Prim.h"

int main() {
	FILE *fin = fopen("in.txt", "r");
	FILE *fout = fopen("out.txt", "w");

	if (fin == NULL) {
		fputs("bad input", fout);
		return 0;
	}

	unsigned int num_vertices;
	unsigned int num_edges;
	fscanf(fin, "%d", &num_vertices);
	fscanf(fin, "%d", &num_edges);
	BadInput(num_vertices, num_edges, fout);

	long long **graph = (long long **)malloc(num_vertices * sizeof(long long*));
	for (int i = 0; i < num_vertices; i++) {
		graph[i] = (long long*)malloc(num_vertices * sizeof(long long));
	}

	for (int i = 0; i < num_vertices; i++)
		for (int j = 0; j < num_vertices; j++)
			graph[i][j] = 0;

	int beg, end;
	long long len;
	for (int i = 0; i < num_edges; i++) {
		if (fscanf(fin, "%d", &beg) == EOF
			|| fscanf(fin, "%d", &end) == EOF || fscanf(fin, "%lld", &len) == EOF) {
			BadNumLines(fout);
		}
		BadInputEdge(num_vertices, beg, end, len, fout);
		beg--;
		end--;

		graph[beg][end] = len;
		graph[end][beg] = len;
	}
	isConnected(graph, num_vertices, fout);


	PrimMST(graph, num_vertices, fout);

	return 0;
}