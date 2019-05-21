#pragma once

#ifndef H_DECODE
#define H_DECODE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include "binary_tree.h"

#define uc unsigned char

void decode(FILE* fout, char* bin, int* cur_pos, node* root, int end_pos, int last_byte, FILE* log, FILE* fin, uc* zip_text);

void unzip(FILE* fin, FILE* fout, FILE* log);

#endif