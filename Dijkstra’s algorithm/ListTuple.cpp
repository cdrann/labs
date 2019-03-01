#include "ListTuple.h"

listTuple *initListTuple(int i) {
	return createNodeTuple(i, 0);
	/*list *S = (list *)malloc(sizeof(list));

	S->nextNode = i;
	S->lenPath = 0;
	S->next = NULL;

	return S;*/
}

listTuple *createNodeTuple(int node, int len) {
	listTuple *S = (listTuple *)malloc(sizeof(listTuple));

	S->nextNode = node;
	S->lenPath = len;
	S->next = NULL;

	return S;
}

void addNodeTuple(listTuple *AdjList, listTuple *node) {
	node->next = AdjList->next;
	AdjList->next = node;

	/* while (AdjList->next)
		AdjList = AdjList->next;
	AdjList->next = node;
	*/
	///Adj->next = Adj->next->next;
}

/*void removeEdge(int target, list *AdjList) {
	while (AdjList->next && AdjList->next->nextNode != target)
		AdjList = AdjList->next;
	AdjList->next = AdjList->next->next;
}

void addEdge() {

}*/