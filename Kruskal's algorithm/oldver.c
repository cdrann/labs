
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define true 1

typedef struct edge {
	int head;
	int tail;
	int len;
} edgeTriple;

edgeTriple createEdge(int h, int t, int l) {
	edgeTriple tr;
	tr.head = h;
	tr.tail = t;
	tr.len = l;
	return tr;
}

typedef struct node {
	edgeTriple edge;
	struct node *prev;
} node;

typedef struct graph {
	node *first;
	node *last;
} graph;

void badInput(FILE *inputfile, int num_vertices, int num_edges, FILE *output_file) {
	if (feof(inputfile)) {
		fputs("bad number of lines", output_file);
		exit(0);
	}
	if (num_vertices == 1) //TODO
		exit(0); 
	if (num_edges == 0) {
		printf("no spanning tree");
		exit(0);
	}
	if (num_vertices < 0 || num_vertices > 5000) {
		fprintf(output_file, "bad number of vertices");
		exit(0);
	}
	if (num_edges < 0 || num_edges >(num_vertices * (num_vertices - 1)) / 2) {
		fprintf(output_file, "bad number of edges");
		exit(0);
	}
}

void badInputArc(int num_vertices, int head, int tail, long long length) {
	if (head < 1 || head > num_vertices || tail < 1 || tail > num_vertices) {
		printf("bad vertex");
		exit(0);
	}
	if (length < 0 || length > INT_MAX) {
		printf("bad length");
		exit(0);
	}
}

typedef struct linearBuffer {
	uint8_t *mem; //pointer to buffer memory
	size_t  totalSize; //in bytes
	size_t  offset;
} linearBuffer;

//non-aligned allocation from linear buffer
void *linearBufferAlloc(linearBuffer *buf, size_t size) {
	if (!buf || !size)
		return NULL;
	size_t newOffset = buf->offset + size;
	if (newOffset <= buf->totalSize) {
		void *ptr = buf->mem + buf->offset;
		buf->offset = newOffset;
		return ptr;
	}
	return NULL; //out of memory
}

linearBuffer createLinearBuff(size_t sizeOfStruct, size_t  lengthOfPool) {
	linearBuffer memPool;

	memPool.mem = (uint8_t *)malloc(sizeOfStruct * lengthOfPool);
	memPool.totalSize = sizeOfStruct * lengthOfPool;
	memPool.offset = 0;

	return memPool;
}

graph graphHolder(edgeTriple triple, graph graph, linearBuffer *memPool) {
	node *S = (node*)linearBufferAlloc(memPool, sizeof(node));
	S->edge = triple;
	S->prev = NULL;

	if (graph.first == NULL) {
		S->prev = graph.first;
		graph.first = graph.last = S;
		return graph;
	}
	if (triple.len >= graph.last->edge.len) {
		graph.last = graph.last->prev = S;
		return graph;
	}
	if (triple.len <= graph.first->edge.len) {
		S->prev = graph.first;
		graph.first = S;
		return graph;
	}

	node *curr = graph.first;
	while (curr->prev != NULL) {
		if (triple.len <= curr->prev->edge.len) {
			S->prev = curr->prev;
			curr->prev = S;
			return graph;
		}
		curr = curr->prev;
	}
}

node *readEdges(FILE *inputfile, int num_vertices, int num_edges, FILE *outputfile) {
	linearBuffer linearBuffer = createLinearBuff(sizeof(node), num_edges);
	graph graph;
	graph.first = graph.last = NULL;
	
	int cntr = 0;
	int head, tail;
	long long len;
	for (int i = 0; i < num_edges; i++) {
		if (fscanf(inputfile, "%d %d %lld", &head, &tail, &len) == EOF) {
			fputs("bad number of lines", outputfile);
			exit(0);
		}
		badInputArc(num_vertices, head, tail, len);
		head--;
		tail--;

		graph = graphHolder(createEdge(head, tail, len), graph, &linearBuffer);
		node *tmp = graph.first;
	}

	return graph.first;
}

edgeTriple **kruskalAlgo(node *graph, int num_vertices, int num_edges) { // O (M log N + N^2)
	if (!graph)
		exit(0);
	int i;

	edgeTriple **edges = (edgeTriple **)malloc(sizeof(edgeTriple *) * num_vertices);
	int *tree_id = (int *)malloc(sizeof(int) * num_vertices);
	for (i = 0; i < num_vertices; ++i) {
		edges[i] = NULL;
		tree_id[i] = i;
	}

	int cntr = 0;
	while (graph) {
		if (tree_id[graph->edge.head] != tree_id[graph->edge.tail]) {
			for (int i = 0; i < num_vertices; ++i) {
				if (edges[i] == NULL) {
					edges[i] = &graph->edge;
					break;
				}
			}
			int old_id = tree_id[graph->edge.tail];
			int new_id = tree_id[graph->edge.head];
			for (int i = 0; i < num_vertices; ++i) {
				if (tree_id[i] == old_id)
					tree_id[i] = new_id;
			}
			cntr++;
		}
		graph = graph->prev;
	}

	if (cntr < num_vertices - 1) {
		printf("no spanning tree");
		exit(0);
	} 

	return edges;
}

void printEdges(FILE *outputfile, edgeTriple **MST_edges, int num_vertices) {
	for (int i = 0; i < num_vertices && MST_edges[i] != NULL; ++i) {
		if (MST_edges[i]->head > MST_edges[i]->tail)
			fprintf(outputfile, "%d %d\n", MST_edges[i]->tail + 1, MST_edges[i]->head + 1);
		else
			fprintf(outputfile, "%d %d\n", MST_edges[i]->head + 1, MST_edges[i]->tail + 1);
	}
}

int main() {
	FILE *inputfile = fopen("in.txt", "r");
	FILE *outputfile = fopen("out.txt", "w");

	if (inputfile == NULL) {
		fputs("no such file", outputfile);
		exit(0);
	}

	unsigned int num_vertices, num_edges;
	fscanf(inputfile, "%d %d", &num_vertices, &num_edges);
	badInput(inputfile, num_vertices, num_edges, outputfile);
	node *graph = readEdges(inputfile, num_vertices, num_edges, outputfile);

	edgeTriple **kruskalRes = kruskalAlgo(graph, num_vertices, num_edges);
	printEdges(outputfile, kruskalRes, num_vertices);

	fclose(inputfile);
	fclose(outputfile);
	return 0;
}
