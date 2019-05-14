#pragma once

#ifndef H_STACK
#define H_STACK

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_MAX_SIZE 10000

typedef struct Stack {
	short data[STACK_MAX_SIZE];
	short size;
} Stack;

Stack *StackConstructor();

void Push(Stack *stack, short N);

void StackDestructor(Stack *stack);

void PrintStackValue(short value, FILE *fout);

void PrintStack(Stack *Stack, FILE *fout);

#endif