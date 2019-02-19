#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define INFINITY -1

void is_bad_input(int num_vertexes, int head, int tail, int num_edges, FILE *output_file) {
	if (num_vertexes < 0 || num_vertexes > 5000) {
		fprintf(output_file, "bad number of vertices");
		exit(0);
	}
	if (head < 1 || head > num_vertexes || tail < 1 || tail > num_vertexes) {
		fprintf(output_file, "bad vertex");
		exit(0);
	}
	if (num_edges < 0 || num_edges > (num_vertexes * (num_vertexes - 1)) / 2) {
		fprintf(output_file, "bad number of edges");
		exit(0);
	}
}

void is_bad_vertex_len(int head, int tail, long long path_len, int num_vertexes, FILE *output_file) {
	if (head < 1 || head > num_vertexes || tail < 1 || tail > num_vertexes) {
		fprintf(output_file, "bad vertex");
		exit(0);
	}
	if (path_len < 0 || path_len > INT_MAX) {
		fprintf(output_file, "bad length");
		exit(0);
	}
}

typedef struct vertex {
	unsigned long long len;
	int single_way;
	int visited;
	int parent;
} node;

int **create_matrix(int num_vertexes) {
	int **matrix = (int **)malloc(num_vertexes * sizeof(int *));
	for (int i = 0; i < num_vertexes; i++) {
		matrix[i] = (int *)malloc(num_vertexes * sizeof(int));
	}

	return matrix;
}

int **fill_in_matrix(int **matrix, int num_edges, int num_vertexes, FILE *input_file, FILE *output_file) {
	int i, j;
	for (i = 0; i < num_vertexes; i++) 
		for (j = 0; j < num_vertexes; j++) 
			matrix[i][j] = INFINITY;
		
	for (i = 0; i < num_edges; ++i) {
		int head, tail;
		long long path_len;

		fscanf(input_file, "%d %d", &head, &tail);
		fscanf(input_file, "%llu", &path_len); //lli

		is_bad_vertex_len(head, tail, path_len, num_vertexes, output_file);
		--head; --tail;
		matrix[head][tail] = path_len;
		matrix[tail][head] = path_len;

		if (feof(input_file) && i < num_edges - 1) {
			fprintf(output_file, "bad number of lines");
			exit(0);
		}
	}

	for (i = 0; i < num_vertexes; i++)
		matrix[i][i] = 0;

	return matrix;
}

node *create_node(int num_vertexes) {
	node *vertex = (node *)malloc(num_vertexes * sizeof(node));
	for (int i = 0; i < num_vertexes; i++) {
		vertex[i].len = INFINITY;
		vertex[i].visited = 0;
		vertex[i].parent = -1;
	}

	return vertex;
}

void algo_dijkstra(int num_vertexes, int **matrix, node *vertexes, int head, int tail) {
	vertexes[head].len = 0;

	for(;;) {
		int v = -1;
		for (int j = 0; j < num_vertexes; ++j)
			if ((!vertexes[j].visited) && ((v == -1) || (vertexes[j].len < vertexes[v].len)))
				v = j;

		if (v == -1) { break; }
		vertexes[v].visited = 1;

		for (int k = 0; k < num_vertexes; ++k) {
			if (k == v) { continue; }
			if (matrix[v][k] != INFINITY) {
				if ((vertexes[v].len + (unsigned long long)matrix[v][k] < vertexes[k].len) 
																			|| (vertexes[k].len == INFINITY)) {

					vertexes[k].len = vertexes[v].len + (unsigned long long)matrix[v][k];
					vertexes[k].parent = v;
					vertexes[k].single_way = 1;
					continue;

				} else if ((vertexes[v].len + (unsigned long long)matrix[v][k]) == vertexes[k].len)
					vertexes[k].single_way = 0;
			}
		}
	} 
}

void print_all_distance(int num_vertexes, FILE *output_file, node *vertexes) {
	for (int i = 0; i < num_vertexes; ++i) {
		long long len = vertexes[i].len;

		if (len == INFINITY) {
			fprintf(output_file, "oo "); // no path
			continue; // NO continue --> else if + else 
		}
		if (len > INT_MAX) {
			fprintf(output_file, "INT_MAX+ ");
			continue;
		}
		fprintf(output_file, "%llu ", len); // %I64d
	}
	fprintf(output_file, "\n");
}

void print_path_head_to_tail(int num_vertexes, int **matrix, node *vertexes, int head, int tail, FILE *output_file) {
	if (vertexes[tail].len == INFINITY) {
		fprintf(output_file, "no path");
		return;
	}

	int p[5001];
	int cntr = 0;

	for (int i = tail; i != head; i = vertexes[i].parent, ++cntr) {
		p[cntr] = i + 1;
		if ((vertexes[i].len > INT_MAX) && (!vertexes[i].single_way)) {
			fprintf(output_file, "overflow"); //длина кратчайшего пути > INT_MAX и путей длины > INT_MAX два или больше
			exit(0);
		}
	}

	for (int i = 0; i < cntr; ++i)
		fprintf(output_file, "%d ", p[i]);

	fprintf(output_file, "%d ", head + 1);
}

void delete_vertex(node *vertex) {
	if (vertex)
		free(vertex);
}

void delete_matrix(int **matrix, int num_vertexes) {
	for (int i = 0; i < num_vertexes; i++)
		free(matrix[i]);
	free(matrix);
}

int main() {
	FILE *input_file = fopen("in.txt", "r");
	FILE *output_file = fopen("out.txt", "w");

	if (input_file == NULL) {
		fputs("no such file", output_file);
		exit(0);
	}

	int num_vertexes, head, tail, num_edges;
	fscanf(input_file, "%d %d %d %d", &num_vertexes, &head, &tail, &num_edges);

	is_bad_input(num_vertexes, head, tail, num_edges, output_file);

	int **matrix = create_matrix(num_vertexes);
	matrix = fill_in_matrix(matrix, num_edges, num_vertexes, input_file, output_file);

	node *vertexes = create_node(num_vertexes);
	algo_dijkstra(num_vertexes, matrix, vertexes, head - 1, tail - 1);

	print_all_distance(num_vertexes, output_file, vertexes);
	print_path_head_to_tail(num_vertexes, matrix, vertexes, head - 1, tail - 1, output_file);

	delete_vertex(vertexes);
	delete_matrix(matrix, num_vertexes);
	fclose(input_file);
	fclose(output_file);
	return 0;
}
