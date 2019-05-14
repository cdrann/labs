#pragma once

#include "stack.h"

#define STACK_OVERFLOW  -100

Stack *StackConstructor() {
	Stack *stack = NULL;
	stack = calloc(1, sizeof(Stack));

	return stack;
}

void Push(Stack *stack, short value) {
	stack->data[stack->size] = value;
	stack->size++;

	if (stack->size >= STACK_MAX_SIZE) {
		exit(STACK_OVERFLOW);
	}
}

void StackDestructor(Stack *stack) {
	free(stack);
}

void PrintStackValue(short value, FILE *fout) {
	fprintf(fout, "%hd ", value);
}

void PrintStack(Stack *Stack, FILE *fout) {
	if (Stack->size == 0) 
		return;

	short i = Stack->size - 1;
	while (i >= 0) {
		PrintStackValue(Stack->data[i], fout);
		i--;
	} 
}