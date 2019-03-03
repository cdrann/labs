#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void is_bad_input(int num_vertexes, int num_edges, FILE *output_file) {
	if (num_vertexes < 0 || num_vertexes > 5000) {
		fprintf(output_file, "bad number of vertices");
		exit(0);
	}
	if (num_edges < 0 || num_edges >(num_vertexes * (num_vertexes - 1)) / 2) {
		fprintf(output_file, "bad number of edges");
		exit(0);
	}
}

int main() {
	FILE *input_file = fopen("in.txt", "r");
	FILE *output_file = fopen("out.txt", "a");

	if (input_file == NULL) {
		fputs("no such file", output_file);
		exit(0);
	}

	int num_vertices, num_edges;
	if (fscanf(input_file, "%d %d", &num_vertices, &num_edges) == EOF) {
		fprintf(output_file, "bad number of lines");
		exit(0);
	}
	is_bad_input(num_vertices, num_edges, output_file);

	graphNode *graph = createGraph(num_vertices);

	int beg, end, len;
	for (int i = 0; i < num_edges; i++) {
		if (fscanf(input_file, "%d %d %lld", &beg, &end, &len) == EOF) {
			fprintf(output_file, "bad number of lines");
			exit(0);
		}
		if (len > (long long)INT_MAX || len < 0) {
			fprintf(output_file, "bad length");
			exit(0);
		}
		addEdge(beg, end, len, graph);
	}
	
	fclose(input_file);
	fclose(output_file);
	return 0;
}
