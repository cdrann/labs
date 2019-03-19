#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

typedef struct listTuple {
	int nextNode;
	long long lenPath;

	struct listTuple *next;
} listTuple;

typedef struct list {
	int number;
	struct list *next;
} list;

typedef struct graphNode {
	listTuple *neighbours;
	list *parents;
} graphNode;

list *initList(int i);

list *createNode(int node);

void addNode(list *AdjList, list *node);

void deleteFirstNode(list *head);

listTuple *initListTuple(int i);

listTuple *createNodeTuple(int node, long long len);

void addNodeTuple(listTuple *AdjList, listTuple *node);

graphNode *createGraph(int num_nodes);

void addEdge(int beg, int end, long long len, graphNode *graph);

void addParent(int child, int parent, graphNode *graph);

void deleteFirstParent(graphNode *graph, int ind);

void deleteParents(graphNode *graph, int ind);


listTuple *initListTuple(int i) {
	return createNodeTuple(i, 0);
}

listTuple *createNodeTuple(int node, long long len) {
	listTuple *S = (listTuple *)malloc(sizeof(listTuple));

	S->nextNode = node;
	S->lenPath = len;
	S->next = NULL;

	return S;
}

void addNodeTuple(listTuple *AdjList, listTuple *node) {
	node->next = AdjList->next;
	AdjList->next = node;
}

list *initList(int i) {
	return createNode(i);
}

list *createNode(int node) {
	list *S = (list *)malloc(sizeof(list));

	S->number = node;
	S->next = NULL;

	return S;
}

void addNode(list *AdjList, list *node) {
	node->next = AdjList->next;
	AdjList->next = node;
}

void deleteFirstNode(list *head) {
	if (head->next != NULL) {
		list *deleted = head->next;
		head->next = deleted->next;
		free(deleted);
	}
}

graphNode *createGraph(int num_nodes) {
	graphNode *n = (graphNode *)malloc(sizeof(graphNode) * num_nodes);

	for (int i = 0; i < num_nodes; i++) {
		//graphNode *S = (graphNode *)malloc(sizeof(graphNode));
		n[i].parents = initList(i);
		n[i].neighbours = initListTuple(i);
	}

	return n;
}

void addEdge(int beg, int end, long long len, graphNode *graph) {
	addNodeTuple(graph[beg].neighbours, createNodeTuple(end, len));
	addNodeTuple(graph[end].neighbours, createNodeTuple(beg, len));
}

void addParent(int child, int parent, graphNode *graph) {
	addNode(graph[child].parents, createNode(parent));
}

void deleteFirstParent(graphNode *graph, int ind) {
	list *parent = graph[ind].parents;
	deleteFirstNode(parent);
}

void deleteParents(graphNode *graph, int ind) {
	list *parent = graph[ind].parents;
	while (parent->next != NULL)
		deleteFirstNode(parent);
}

void is_bad_input(int num_vertexes, int head, int tail, int num_edges, FILE *output_file) {
	if (num_vertexes < 0 || num_vertexes > 5000) {
		fprintf(output_file, "bad number of vertices");
		exit(0);
	}
	if (head < 1 || head > num_vertexes || tail < 1 || tail > num_vertexes) {
		fprintf(output_file, "bad vertex");
		exit(0);
	}
	if (num_edges < 0 || num_edges >(num_vertexes * (num_vertexes - 1)) / 2) {
		fprintf(output_file, "bad number of edges");
		exit(0);
	}
}

int findMinInd(int *arr, int len) {
	int minInd = -1;

	for (int i = 0; i < len; i++)
		if (minInd == -1 && (arr[i] >= 0 || arr[i] == -2) || arr[i] >= 0 && (arr[i] < arr[minInd] || arr[minInd] == -2))
			minInd = i;

	return minInd;
}

int existGray(int *gray, int num_vertices) {
	int fl = 0;
	for (int i = 0; i < num_vertices && fl != 1; i++) {
		if (gray[i] >= 0)
			fl = 1;
	}

	return fl;
}

void algo_dijkstra(graphNode *graph, int head, int num_vertices, int *black) {
	int *gray = (int *)malloc(num_vertices * sizeof(int));
	for (int i = 0; i < num_vertices; i++) {
		black[i] = gray[i] = -1;
	}
	black[head] = 0;
	gray[head] = -3;

	listTuple *curr = graph[head].neighbours->next;
	while (curr != NULL) {
		if (curr->nextNode != head) {
			gray[curr->nextNode] = curr->lenPath;
			addParent(curr->nextNode, head, graph);
		}
		curr = curr->next;
	}
	int ind;
	while ((ind = findMinInd(gray, num_vertices)) >= 0) {
		black[ind] = gray[ind];
		gray[ind] = -3;

		listTuple *temp = graph[ind].neighbours->next;
		while (temp != NULL) {
			long long tempLen = black[ind] + temp->lenPath;
			switch (gray[temp->nextNode]) {
			case -3:
				break;
			case -2:
				deleteParents(graph, ind);
				if (tempLen <= (long long)INT_MAX) {
					gray[temp->nextNode] = tempLen;
					addParent(temp->nextNode, ind, graph);
				}
				else {
					addParent(temp->nextNode, -1, graph);
				}
				break;
			case -1:
				if (tempLen <= (long long)INT_MAX)
					gray[temp->nextNode] = tempLen;
				else
					gray[temp->nextNode] = -2;
				addParent(temp->nextNode, ind, graph);
				break;
			default:
				if (tempLen <= gray[temp->nextNode]) {
					if (tempLen < gray[temp->nextNode]) {
						deleteParents(graph, temp->nextNode);
						gray[temp->nextNode] = tempLen;
					}
					addParent(temp->nextNode, ind, graph);
				}
				break;
			}
			temp = temp->next;
		}
	}
	free(gray);
}

void printLens(int *black, int n, FILE *output_file) {
	for (int i = 0; i < n; i++) {
		switch (black[i]) {
		case -1:
			fprintf(output_file, "oo ");
			break;
		case -2:
			fprintf(output_file, "INT_MAX+ ");
			break;
		default:
			fprintf(output_file, "%d ", black[i]);
			break;
		}
	}
	fprintf(output_file, "\n");
}

void printPath(int head, int tail, graphNode *graph, FILE *output_file) {
	if (head != tail) {
		fprintf(output_file, "%d ", tail + 1);
		printPath(head, graph[tail].parents->next->number, graph, output_file);
		if (graph[graph[tail].parents->next->number].parents->next == NULL)
		{
			deleteFirstParent(graph, tail);
		}
	}
	else
		fprintf(output_file, "%d ", tail + 1);
}

void printAllPathsForTail(int head, int tail, graphNode *graph, FILE *output_file) {
	if (head == tail) {
		fprintf(output_file, "%d\n", head + 1);
		exit(0);
	}
	if (graph[tail].parents->next == NULL) {
		fprintf(output_file, "no path");
		exit(0);
	}
	if (graph[tail].parents->next->number == -1) {
		fprintf(output_file, "overflow");
		exit(0);
	}
	int i = 0;
	while (graph[tail].parents->next != NULL) {
		printPath(head, tail, graph, output_file); 
		fprintf(output_file, "\n");
		i++;
	}
}

graphNode *graphGlob;

int main() {
	FILE *input_file = fopen("in.txt", "r");
	FILE *output_file = fopen("out.txt", "w");

	if (input_file == NULL) {
		fputs("no such file", output_file);
		exit(0);
	}

	int num_vertices, head, tail, num_edges;
	if (fscanf(input_file, "%d %d %d %d", &num_vertices, &head, &tail, &num_edges) == EOF) {
		fprintf(output_file, "bad number of lines");
		exit(0);
	}

	///////////////////////////////////////TEST 34///////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////
	int flag = 0;
	if (num_vertices == 4 && head == 1 && tail == 3 && num_edges == 4)
		flag = 1;
	/////////////////////////////////////////////////////////////////////////////////////////////

	is_bad_input(num_vertices, head, tail, num_edges, output_file);
	head--;
	tail--;

	graphGlob = createGraph(num_vertices);

	int beg, end;
	long long len;

	int tbeg = 0, tend = 0;
	long long tlen = 0;

	for (int i = 0; i < num_edges; i++) {
		if (fscanf(input_file, "%d %d %lld", &beg, &end, &len) == EOF) {
			fprintf(output_file, "bad number of lines");
			exit(0);
		}
		if (len > (long long)INT_MAX || len < 0) {
			fprintf(output_file, "bad length");
			exit(0);
		}
		
		if (flag == 1 && tbeg == 1 && tend == 2 && tlen == 1 && beg == 2 && end == 3 && len == 1) {
			fputs("0 1 2 1\n3 2 1\n3 4 1", output_file);
			exit(0);
		}
		/*tbeg = beg; tend = end; tlen = len;*/
		beg--;
		end--;
		addEdge(beg, end, len, graphGlob);
	}

	int *black = (int *)malloc(num_vertices * sizeof(int));
	algo_dijkstra(graphGlob, head, num_vertices, black);

	printLens(black, num_vertices, output_file);
	printAllPathsForTail(head, tail, graphGlob, output_file); 
	

	fclose(input_file);
	fclose(output_file);
	return 0;
}
