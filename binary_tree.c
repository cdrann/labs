#pragma once

#include "binary_tree.h"
#define INF (int)1e9

void char_to_bin(uc c, char* bin_code) {
	int k = 128;
	for (int i = 0; i < 8; ++i) {
		bin_code[i] = (bool)(c&k) ? (char)'1' : (char)'0';
		k >>= 1;
	}
	bin_code[8] = '\0';
}

void bin_to_char(const char* bin, uc* c) {
	int res = 0;
	for (int i = 0; i < 8; ++i) {
		res += (int)pow(2, 7 - i) * (bin[i] - '0');
	}
	*c = (uc)res;
}

node* build_tree(node* mas, int symb_sum) {
	node* min1 = (mas[0].sum < mas[1].sum) ? &mas[0] : &mas[1];
	node* min2 = (mas[0].sum < mas[1].sum) ? &mas[1] : &mas[0];
	for (int i = 2; i < symb_sum; ++i) {
		if (mas[i].sum < min1->sum && mas[i].sum < min2->sum) {
			min2 = min1;
			min1 = &mas[i];
		}
		else if (mas[i].sum < min2->sum) {
			min2 = &mas[i];
		}
	}

	if (min2->sum == INF) {
		return min1;
	}

	mas[symb_sum].is_leaf = false;
	mas[symb_sum].to1 = min2;
	mas[symb_sum].to0 = min1;
	mas[symb_sum].sum = min1->sum + min2->sum;
	symb_sum++;

	min1->sum = INF;
	min2->sum = INF;

	return build_tree(mas, symb_sum);
}

void get_code(node* cur_node, char cur_code[], int cur_pos) {
	if (cur_node->is_leaf) {
		if (cur_pos == 0) {
			strcpy(cur_node->code, "1\0");
			return;
		}
		cur_code[cur_pos] = '\0';
		strcpy(cur_node->code, cur_code);
		return;
	}

	cur_code[cur_pos] = '0';
	get_code(cur_node->to0, cur_code, cur_pos + 1);
	cur_code[cur_pos] = '1';
	get_code(cur_node->to1, cur_code, cur_pos + 1);
}

void make_dir(node* cur_node, char* cur_dir, int* cur_size) {
	if (cur_node->is_leaf) {
		cur_dir[*cur_size] = '0';
		(*cur_size)++;
		char bin_code[9];
		char_to_bin(cur_node->symb, &bin_code[0]);
		for (int i = 0; i < 8; ++i) {
			cur_dir[*cur_size + i] = bin_code[i];
			cur_dir[*cur_size + i + 1] = '\0';
		}
		*cur_size += 8;
		return;
	}

	cur_dir[*cur_size] = '1';
	(*cur_size)++;
	if (cur_node->to1->is_leaf) {
		cur_dir[*cur_size] = '0';
		(*cur_size)++;
		char bin_code[9];
		char_to_bin(cur_node->to1->symb, &bin_code[0]);
		for (int i = 0; i < 8; ++i) {
			cur_dir[*cur_size + i] = bin_code[i];
			cur_dir[*cur_size + i + 1] = '\0';
		}
		*cur_size += 8;
	}
	else {
		make_dir(cur_node->to1, cur_dir, cur_size);
	}

	if (cur_node->to0->is_leaf) {
		cur_dir[*cur_size] = '0';
		(*cur_size)++;
		char bin_code[9];
		char_to_bin(cur_node->to0->symb, &bin_code[0]);
		for (int i = 0; i < 8; ++i) {
			cur_dir[*cur_size + i] = bin_code[i];
			cur_dir[*cur_size + i + 1] = '\0';
		}
		*cur_size += 8;
	}
	else {
		make_dir(cur_node->to0, cur_dir, cur_size);
	}
}

node* build_unzip_tree(const char* bin, int* cur_pos, node* cur_node, int* free_node_pos, node* nodes) {
	if (bin[*cur_pos] == '0') {
		cur_node->is_leaf = true;
		(*cur_pos)++;
		char bin8[9];
		for (int i = 0; i < 8; i++, (*cur_pos)++) {
			bin8[i] = bin[*cur_pos];
		}
		bin8[8] = '\0';
		bin_to_char(bin8, &cur_node->symb);
	}

	else {
		cur_node->is_leaf = false;
		(*cur_pos)++;
		cur_node->to1 = &nodes[*free_node_pos];
		(*free_node_pos)++;
		build_unzip_tree(bin, cur_pos, cur_node->to1, free_node_pos, nodes);
		cur_node->to0 = &nodes[*free_node_pos];
		(*free_node_pos)++;
		build_unzip_tree(bin, cur_pos, cur_node->to0, free_node_pos, nodes);

	}
}