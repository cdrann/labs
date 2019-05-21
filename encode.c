#pragma once

#include "encode.h"
#include "binary_tree.h"

#define BUF_SIZE (int)1e4
#define INF (int)1e9
#define uc unsigned char

int print_bin(char* bin, FILE* fout, FILE* log) {
	int size = strlen(bin);
	int bin_pos = 0;
	int k = 0;
	size_t zip_pos = 0;
	uc* zipped = (uc*)malloc(sizeof(uc)*(BUF_SIZE + 1));
	if (zipped == NULL) {
		fprintf(log, "mem error");
		exit(0);
	}
	while (bin_pos < size) {
		char bin8[9];
		for (int i = 0; i < 8; i++, bin_pos++) {
			if (bin_pos >= size) {
				bin8[i] = '0';
				k++;
				continue;
			}
			bin8[i] = bin[bin_pos];
		}
		bin8[8] = '\0';
		uc tmp;
		bin_to_char(bin8, &tmp);
		zipped[zip_pos] = tmp;
		zipped[zip_pos + 1] = '\0';
		zip_pos++;
	}
	fwrite(zipped, sizeof(unsigned char), zip_pos, fout);
	free(zipped);
	return k;
}

void zip(FILE* fin, FILE* fout, FILE* log) {
	node* nodes = (node*)malloc(sizeof(node) * 513);
	if (nodes == NULL) {
		fprintf(log, "mem error");
		exit(0);
	}
	for (int i = 0; i < 256; ++i) {
		nodes[i].is_leaf = false;
		nodes[i].to0 = NULL;
		nodes[i].to1 = NULL;
		nodes[i].symb = (uc)i;
		nodes[i].sum = 0;
		nodes[i].code = (char*)malloc(sizeof(char) * 100);
		if (nodes[i].code == NULL) {
			fprintf(log, "mem error");
			exit(0);
		}
	}

	uc* text = (uc*)malloc(sizeof(uc)*(BUF_SIZE + 1));
	if (text == NULL) {
		fprintf(log, "mem error");
		exit(0);
	}
	int to_zip_size = 0;

	while (1) {
		int fsize = fread(text, sizeof(uc), BUF_SIZE, fin);
		if (fsize == 0) break;

		for (int i = 0; i < fsize; ++i) {
			nodes[(int)text[i]].sum++;
			nodes[(int)text[i]].is_leaf = true;
			to_zip_size++;
		}
	}

	for (int i = 0; i < 256; ++i) {
		if (nodes[i].sum == 0) {
			nodes[i].sum = INF;
			continue;
		}
	}
	int symb_sum = 256;

	node* root = build_tree(&nodes[0], symb_sum);

	char start_code[101];
	get_code(root, start_code, 0);

	char* bin_zip = (char*)malloc(sizeof(char)*(8 * (BUF_SIZE + 1)) + 1);
	if (bin_zip == NULL) {
		fprintf(log, "mem error");
		exit(0);
	}
	int code_size = 0;
	make_dir(root, bin_zip, &code_size);

	fseek(fin, 0, SEEK_SET);
	unsigned char tmp[4];
	fread(tmp, sizeof(unsigned char), 3, fin);

	int fsize = fread(text, sizeof(uc), BUF_SIZE, fin);

	for (int i = 0; i < fsize; ++i) {
		for (int j = 0; j < strlen(nodes[text[i]].code); ++j) {
			bin_zip[code_size] = nodes[text[i]].code[j];
			bin_zip[code_size + 1] = '\0';
			code_size++;
			if (code_size == 8 * BUF_SIZE) {
				print_bin(bin_zip, fout, log);
				code_size = 0;
				bin_zip[0] = '\0';
			}
		}
		if (i == fsize - 1) {
			fsize = fread(text, sizeof(uc), BUF_SIZE, fin);
			i = -1;
		}
	}

	tmp[0] = (uc)(print_bin(bin_zip, fout, log) + '0');
	fwrite(tmp, sizeof(unsigned char), 1, fout);
	free(text);
	free(bin_zip);
}