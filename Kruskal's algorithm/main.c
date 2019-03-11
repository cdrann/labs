#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void is_bad_input(int num_vertices, int num_edges, FILE *output_file) {
	if (num_vertices < 0 || num_vertices > 5000) {
		fprintf(output_file, "bad number of vertices");
		exit(0);
	}
	if (num_edges < 0 || num_edges >(num_vertices * (num_vertices - 1)) / 2) {
		fprintf(output_file, "bad number of edges");
		exit(0);
	}
}

typedef struct {
	int* Parent;
	int* Rank;
} TDSU;

//Создает систему непересекающихся множеств, состоящую из всех одноэлементных подмножеств finiteSet
TDSU* MakeSets(int count) {
	TDSU* dsu = malloc(sizeof(TDSU));
	assert(dsu != NULL);
	dsu->Parent = calloc(count, sizeof(int));
	assert(dsu->Parent != NULL);
	for (int element = 0; element < count;
		++element) {
		dsu->Parent[element] = element;
	}
	dsu->Rank = calloc(count, sizeof(int));
	assert(dsu->Rank != NULL);
	return dsu;
}

void DestroySets(TDSU* dsu) {
	free(dsu->Parent);
	free(dsu->Rank);
	free(dsu);
}

//Возвращает множество из disjointSets, которое содержит element
int FindSet(TDSU* dsu, int element) {
	if (element == dsu->Parent[element]) {
		return element;
	}
	dsu->Parent[element] =
		FindSet(dsu, dsu->Parent[element]);
	return dsu->Parent[element];
}

//Преобразует disjointSets, объединяя множества setForX и setForY
void MergeSets(TDSU* dsu, int setX, int setY) {
	assert(dsu->Parent[setX] == setX);
	assert(dsu->Parent[setY] == setY);
	if (dsu->Rank[setX] > dsu->Rank[setY]) {
		dsu->Parent[setY] = setX;
		return;
	}
	dsu->Parent[setX] = setY;
	if (dsu->Rank[setX] == dsu->Rank[setY]) {
		dsu->Rank[setY] += 1;
	}
}
/* void KrusalMinimumSpanningTree(graph, weight[]) {
	sortedEdges = SortAscending(
		graph.Edges,
		cmp(left, right) :
		return weight[left] < weight[right]
	)

		connectedComponents = MakeSets(graph.Vertices)

		treeVertices = graph.Vertices
		treeEdges = 
		for (u, v)  sortedEdges :
	setForU = FindSet(connectedComponents, u)
		setForV = FindSet(connectedComponents, v)
		if setForU != setForV :
			treeEdges += treeEdges
			MergeSets(connectedComponents, setForU, setForV)

			return MakeGraph(treeVertices, treeEdges)

} */

int main() {
	FILE *input_file = fopen("in.txt", "r");
	FILE *output_file = fopen("out.txt", "a");

	if (input_file == NULL) {
		fputs("no such file", output_file);
		exit(0);
	}

	int num_vertices, num_edges;
	fscanf(input_file, "%d %d", &num_vertices, &num_edges);
	is_bad_input(num_vertices, num_edges, output_file);

	graphNode *graph = createGraph(num_vertices);

	int beg, end;
	long long len;
	for (int i = 0; i < num_edges; i++) {
		if (fscanf(input_file, "%d %d %lld", &beg, &end, &len) == EOF) {
			fprintf(output_file, "bad number of lines");
			exit(0);
		}
		if (len > INT_MAX || len < 0) {
			fprintf(output_file, "bad length");
			exit(0);
		}
		addEdge(beg, end, len, graph);
	}

	fclose(input_file);
	fclose(output_file);
	return 0;
}
