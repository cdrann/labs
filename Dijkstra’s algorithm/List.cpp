#include "List.h"

list *initList(int i) {
	return createNode(i);
	/*list *S = (list *)malloc(sizeof(list));

	S->nextNode = i;
	S->lenPath = 0;
	S->next = NULL;

	return S;*/
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

void deleteNode(int n) {
	//удалить нод по значению n
}