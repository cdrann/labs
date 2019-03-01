#include "Graph.h"

graphNode *createGraph(int num_nodes) {
	graphNode *n = (graphNode *)malloc(sizeof(graphNode) * num_nodes);

	for (int i = 0; i < num_nodes; i++) {
		//graphNode *S = (graphNode *)malloc(sizeof(graphNode));
		n[i].parents = initList(i);
		n[i].neighbours = initListTuple(i);
	}

	return n;
}

void addEdge(int beg, int end, int len, graphNode *graph) {
	addNodeTuple(graph[beg].neighbours, createNodeTuple(end, len));
	addNodeTuple(graph[end].neighbours, createNodeTuple(beg, len));
}

void addParent(int child, int parent, graphNode *graph) {
	addNode(graph[child].parents, createNode(parent));
}

void deleteParent() {

}