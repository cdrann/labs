#pragma once

#ifndef H_BIN_TREE
#define H_BIN_TREE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#define uc unsigned char

typedef struct node node;
struct node {
	node* to1;
	node* to0;
	int sum;
	bool is_leaf;
	uc symb;
	char* code;
};

void char_to_bin(uc c, char* bin_code);

void bin_to_char(const char* bin, uc* c);

node *build_tree(node* mas, int symb_sum);

void get_code(node* cur_node, char cur_code[], int cur_pos);

void make_dir(node* cur_node, char* cur_dir, int* cur_size);

node* build_unzip_tree(const char* bin, int* cur_pos, node* cur_node, int* free_node_pos, node* nodes);

#endif