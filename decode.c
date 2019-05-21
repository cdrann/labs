#pragma once

#include "decode.h"
#define BUF_SIZE (int)1e4
#define uc unsigned char

void decode(FILE* fout, char* bin, int* cur_pos, node* root, int end_pos, int last_byte, FILE* log, FILE* fin, uc* zip_text) {
	node* cur_node = root;
	uc* out = (uc*)malloc(sizeof(uc)*(8 * (BUF_SIZE + 1)));
	if (out == NULL) {
		fprintf(log, "mem error");
		exit(0);
	}

	size_t out_pos = 0;

	for (; *cur_pos < end_pos; ++(*cur_pos)) {
		if (end_pos - (*cur_pos) == last_byte && end_pos < 8 * (BUF_SIZE - 1)) {
			fwrite(out, sizeof(uc), out_pos, fout);
			break;
		}

		if (root->is_leaf) {
			out[out_pos] = root->symb;
			out[out_pos + 1] = '\0';
			out_pos++;
		}

		else {
			if (bin[*cur_pos] == '1') {
				cur_node = cur_node->to1;
			}

			else {
				cur_node = cur_node->to0;
			}

			if (cur_node->is_leaf) {
				out[out_pos] = cur_node->symb;
				out[out_pos + 1] = '\0';
				out_pos++;
				cur_node = root;
			}
		}

		if (*cur_pos == end_pos - 1) {
			fwrite(out, sizeof(uc), out_pos, fout);
			int fsize = fread(zip_text, sizeof(uc), (size_t)(BUF_SIZE - 1), fin);
			if (fsize == 0) break;
			char bin_code[9];
			char_to_bin((uc)(last_byte + '0'), &bin_code[0]);
			for (int j = 0; j < 9; ++j) {
				bin[j] = bin_code[j];
			}
			end_pos = 8;

			for (int i = 0; i < fsize - 1; ++i) {
				char_to_bin(zip_text[i], &bin_code[0]);
				for (int j = 0; j < 9; ++j) {
					bin[end_pos + j] = bin_code[j];
				}
				end_pos += 8;
			}
			last_byte = zip_text[fsize - 1] - '0';

			*cur_pos = -1;
			out_pos = 0;
		}
	}
}

void unzip(FILE* fin, FILE* fout, FILE* log) {
	uc* zip_text = (uc*)malloc(sizeof(uc)*(BUF_SIZE + 1));
	if (zip_text == NULL) {
		fprintf(log, "mem error");
		exit(0);
	}
	char* bin_zip = (char*)malloc(sizeof(char)*(8 * (BUF_SIZE + 1) + 1));
	if (bin_zip == NULL) {
		fprintf(log, "mem error");
		exit(0);
	}

	bin_zip[0] = '\0';
	int unzip_size = 0;
	int last_byte = 0;

	int fsize = fread(zip_text, sizeof(uc), BUF_SIZE, fin);
	for (int i = 0; i < fsize - 1; ++i) {
		char bin_code[9];
		char_to_bin(zip_text[i], &bin_code[0]);
		for (int j = 0; j < 9; ++j) {
			bin_zip[unzip_size + j] = bin_code[j];
		}
		unzip_size += 8;
	}
	last_byte = zip_text[fsize - 1] - '0';

	if (unzip_size == 0) exit(0);

	int cur_pos = 0;
	node* nodes = (node*)malloc(sizeof(node) * 512);
	if (nodes == NULL) {
		fprintf(log, "mem error");
		exit(0);
	}

	int free_node_pos = 1;
	build_unzip_tree(bin_zip, &cur_pos, &nodes[0], &free_node_pos, &nodes[0]);
	decode(fout, bin_zip, &cur_pos, &nodes[0], unzip_size, last_byte, log, fin, zip_text);
	free(bin_zip);

}